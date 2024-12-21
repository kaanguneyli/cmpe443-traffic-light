#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "UART.h"
#include "defines.h"
#include "GPIO.h"
#include "mu_json.h"
#include "mu_str.h"

void LPUART1_initialization(void) {
	RCC_APB1ENR1 |= 1 << 28;
	PWR_CR1 |= 1 << 14;
	PWR_CR2 |= 1 << 9;
	RCC_CCIPR1 &= ~(1 << 11);
	RCC_CCIPR1 |= 1 << 10;
	RCC_AHB2ENR |= 1 << 6;
	GPIOG->MODER &= ~(0b0101 << (7 * 2));
	GPIOG->MODER |= 0b1010 << (7 * 2);
	GPIOG->AFRL &= ~(0b0111 << (7 * 4));
	GPIOG->AFRL |= 0b1000 << (7 * 4);
	GPIOG->AFRH &= ~0b0111;
	GPIOG->AFRH |= 0b1000;
	RCC_APB1ENR2 |= 1;
	LPUART1->BRR = 8888;
	LPUART1->CR1 |= 1 << 29;
	LPUART1->CR1 |= 0b11 << 2;
	LPUART1->CR1 |= 1 << 5;
	ISER2 |= 1 << 2;
	LPUART1->CR1 |= 1;
	LPUART1->ICR |= (1 << 6);
	LPUART1->CR1 |= 1 << 6;
}
TrafficLight GeneralTraficLight = { 10, 1, 10, 1, 3, 1 };

char TXmessage[512];
bool eof = true;

void send_Message_recursive() {
	static char *char2send = TXmessage;
	if ((*char2send == 0) || (char2send == TXmessage + 256)) {
		char2send = TXmessage;
		eof = true;
		LPUART1->ICR |= (1 << 6);
	} else {
		LPUART1->TDR = *char2send;
		char2send++;
	}
}

bool send_message_NB(const char *string) {
	if (eof) {
		strlcpy(TXmessage, string, sizeof(TXmessage));
		eof = false;
		send_Message_recursive();
	}
	return eof;
}

bool send_message_B(char *string) {
	if (eof) {
		int i = 0;
		while (string[i] != '\0') {
			LPUART1->TDR = string[i];
			while ((LPUART1->ISR & (1 << 6)) == 0)
				;
			i++;
		}
	}
	return eof;
}

int str2int(const char *str, size_t n) {
	// Create a temporary buffer for the first n characters
	char temp[n + 1];
	strncpy(temp, str, n);  // Copy the first n characters
	temp[n] = '\0';         // Null-terminate the temporary string

	return atoi(temp);      // Convert to integer
}

void process_json(const char *json) {
	mu_json_token_t tokens[128]; // Adjust size as needed
	char err_message[512];
	int n_tokens = mu_json_parse_c_str(tokens, 128, json, NULL);
	if (n_tokens < 0) {
		send_message_NB("Error parsing JSON\r\n");
		return;
	}

	mu_json_token_t *t = &tokens[0];
	if (mu_json_token_type(t) != MU_JSON_TOKEN_TYPE_OBJECT) {
		send_message_NB("Not a JSON object! Aborting...\r\n");
		return;
	}
	for (int j = 1;
			j < n_tokens
					&& mu_json_token_depth(&tokens[j]) > mu_json_token_depth(t);
			j++) {
		mu_str_t *key_mu_str = mu_json_token_slice(&tokens[j]);
		const char *key = (const char*) mu_str_buf(key_mu_str);
		int key_size = (int) mu_str_length(key_mu_str);
		if (mu_json_token_type(&tokens[j]) != MU_JSON_TOKEN_TYPE_STRING) {
			sprintf(err_message, "Key %.*s is not a string! Aborting...\r\n",
					key_size, key);
			send_message_NB(err_message);
			return;
		}
		j++;
		if (j >= n_tokens) {
			sprintf(err_message,
					"Value of key %.*s is not given! Aborting...\r\n", key_size,
					key);
			send_message_NB(err_message);
			return;
		}
		mu_str_t *value_mu_str = mu_json_token_slice(&tokens[j]);
		if (mu_json_token_type(&tokens[j]) != MU_JSON_TOKEN_TYPE_INTEGER) {
			sprintf(err_message,
					"Value of %.*s is not an integer! Aborting...\r\n",
					key_size, key);
			send_message_NB(err_message);
			return;
		}
		uint16_t int_value = mu_str_parse_uint16(value_mu_str);
		if (strncmp("\"red_duration\"", key, key_size) == 0) {
			GeneralTraficLight.red_duration = int_value;
		} else if (strncmp("\"yellow_duration\"", key, key_size) == 0) {
			GeneralTraficLight.yellow_duration = int_value;
		} else if (strncmp("\"green_duration\"", key, key_size) == 0) {
			GeneralTraficLight.green_duration = int_value;
		} else if (strncmp("\"pedestrian_wait\"", key, key_size) == 0) {
			GeneralTraficLight.pedestrian_wait = int_value;
		} else if (strncmp("\"animation_duration\"", key, key_size) == 0) {
			GeneralTraficLight.animation_duration = int_value;
		} else if (strncmp("\"car_wait\"", key, key_size) == 0) {
			GeneralTraficLight.car_wait = int_value;
		} else {
			sprintf(err_message, "Key %.*s is not a defined! Aborting...\r\n",
					key_size, key);
			send_message_NB(err_message);
			return;
		}
	}
}

char RXmessage[512];

void LPUART1_IRQHandler(void) {
	static char *char_read = RXmessage;
	if (RXNFE) {
		char LPUART1_read_value = LPUART1->RDR;
		*char_read = LPUART1_read_value;
		if (LPUART1_read_value == '\0' || LPUART1_read_value == '\r') {
			*char_read = '\0';
			char_read = RXmessage;
//			send_message_NB(RXmessage);
			// Read_coming json
			process_json(RXmessage);
		} else {
			char_read++;
		}

	} else if (TC) {
		if (!eof) {
			send_Message_recursive();
		}

	}
}
