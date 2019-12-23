
#include "Keyboard.h"

namespace dRobot {


/* PRIVATE */

/* Personal private functions */

void Keyboard::setupNextInput(){
	HAL_UART_Receive_IT(huart_pc, cbuf, 1);
}

void Keyboard::interpretInput(uint8_t input_c){
	float_odr vodr;
	uint8_odr todr;
	twist_odr wodr;

	switch(input_c){
	case 'm':
		if (mode == 0){
			mode = 1;
		}
		else{
			mode = 0;
		}

		break;

	case 'w':
		if (mode == 0){
			volume[ch] += 0.1f;

			vodr.val = volume[ch];

			if (volume_dev[ch] != nullptr){
				volume_dev[ch]->shareOdr(vodr);
			}
		}
		else{
			twist[0] += 0.05f;

			wodr.vx = twist[0];
			wodr.vy = twist[1];
			wodr.omega = twist[2];

			if (twist_dev != nullptr){
				twist_dev->shareOdr(wodr);
			}
		}

		break;

	case 's':
		if (mode == 0){
			volume[ch] -= 0.1f;

			vodr.val = volume[ch];

			if (volume_dev[ch] != nullptr){
				volume_dev[ch]->shareOdr(vodr);
			}
		}
		else{
			twist[0] -= 0.05f;

			wodr.vx = twist[0];
			wodr.vy = twist[1];
			wodr.omega = twist[2];

			if (twist_dev != nullptr){
				twist_dev->shareOdr(wodr);
			}
		}

		break;

	case 'a':
		if (mode == 0){
			toggle[ch] = 1 - toggle[ch];

			todr.val = toggle[ch];

			if (toggle_dev[ch] != nullptr){
				toggle_dev[ch]->shareOdr(todr);
			}
		}
		else{
			twist[1] += 0.05f;

			wodr.vx = twist[0];
			wodr.vy = twist[1];
			wodr.omega = twist[2];

			if (twist_dev != nullptr){
				twist_dev->shareOdr(wodr);
			}
		}

		break;

	case 'd':
		if (mode == 1){
			twist[1] -= 0.05f;

			wodr.vx = twist[0];
			wodr.vy = twist[1];
			wodr.omega = twist[2];

			if (twist_dev != nullptr){
				twist_dev->shareOdr(wodr);
			}
		}

		break;

	case 'j':
		if (mode == 1){
			twist[2] += 0.05f;

			wodr.vx = twist[0];
			wodr.vy = twist[1];
			wodr.omega = twist[2];

			if (twist_dev != nullptr){
				twist_dev->shareOdr(wodr);
			}
		}

		break;

	case 'k':
		if (mode == 1){
			twist[2] -= 0.05f;

			wodr.vx = twist[0];
			wodr.vy = twist[1];
			wodr.omega = twist[2];

			if (twist_dev != nullptr){
				twist_dev->shareOdr(wodr);
			}
		}

		break;

	case 'q':
		if (mode == 0){
			volume[ch] = 0.0f;
			toggle[ch] = 0;

			vodr.val = volume[ch];
			todr.val = toggle[ch];

			if (volume_dev[ch] != nullptr){
				volume_dev[ch]->shareOdr(vodr);
			}

			if (toggle_dev[ch] != nullptr){
				toggle_dev[ch]->shareOdr(todr);
			}
		}
		else{
			twist[0] = 0.0f;
			twist[1] = 0.0f;
			twist[2] = 0.0f;

			wodr.vx = twist[0];
			wodr.vy = twist[1];
			wodr.omega = twist[2];

			if (twist_dev != nullptr){
				twist_dev->shareOdr(wodr);
			}
		}

		break;

	default:
		if (input_c >= '0' && input_c <= '9'){
			ch = input_c - '0';
		}
	}
}

} /* namespace dRobot */
