char*	itoa(unsigned int change_me){
	char* result;// = malloc(sizeof(char[2]));
	result = (char *) malloc(sizeof(char[2]));
	unsigned int temp;
	temp = change_me%10;
	
	switch(temp){
		case 0 :
			result[0] = '0';
			break;
		case 1 :
			result[0] = '1';
			break;
		case 2 :
			result[0] = '2';
			break;
		case 3 :
			result[0] = '3';
			break;
		case 4 :
			result[0] = '4';
			break;
		case 5 :
			result[0] = '5';
			break;
		case 6 :
			result[0] = '6';
			break;
		case 7 :
			result[0] = '7';
			break;
		case 8 : 
			result[0] = '8';
			break;
		case 9 :
			result[0] = '9';
			break;
		default :
			result[0] = 'E';
			break;
	}
	
	temp = change_me - change_me%10;
	
	switch(temp){
		case 0 :
			result[1] = '0';
			break;
		case 1 :
			result[1] = '1';
			break;
		case 2 :
			result[1] = '2';
			break;
		case 3 :
			result[1] = '3';
			break;
		case 4 :
			result[1] = '4';
			break;
		case 5 :
			result[1] = '5';
			break;
		case 6 :
			result[1] = '6';
			break;
		case 7 :
			result[1] = '7';
			break;
		case 8 : 
			result[1] = '8';
			break;
		case 9 :
			result[1] = '9';
			break;
		default :
			result[1] = 'E';
			break;
	}
	
	return result;
}