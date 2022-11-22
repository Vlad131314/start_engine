
SIGNAL (SIG_INTERRUPT0) //подпрограмма обработки прерывания от датчика Zero-Cross T = 10ms
{ 
	drv_faza0 = 1; //флаг на формирование задержки от перехода через ноль
	trip++; //перебор значений ШИМ из массива
	if (trip >= count_trip) trip = 0;
};


void zero_init(void)
{
	GICR = 0x40; // int0 enable
	MCUCR = 0x02;// int0 rising edge
};

void drv_act(void)
{
	if (drv_mode == 0) // стоп двигатель
	{
		cbi(PORT_DRV, PIN_DRV);//команда на стоп DRV = 0
		return;
	};
	if (drv_faza0 == 1) //фаза формирование задержки продолжается... 
		{
			cbi(PORT_DRV, PIN_DRV); //команда на стоп DRV = 0
			pwm_trip = pwm_array[trip];
			if (drv_count >= pwm_trip) //значение счетчика задержки сравнить с заданным значением
			 {
			 	drv_faza0 = 0; // флаг на завершение задержки
				drv_count = 0;
			 };
			 drv_count++;
		}
	else  sbi(PORT_DRV, PIN_DRV);// DRV = 1
};

