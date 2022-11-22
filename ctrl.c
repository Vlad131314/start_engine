void NormalCtrl(void)
{ u08 dirctrl;
  
  
  if (rpm > setrpm) 
   {
    delta = rpm - setrpm;
	dirctrl = 0;
   }
  else
   {
    delta = setrpm - rpm;
	dirctrl = 1;
   }; 

  
  if (setrpm > 700) 
  {
  	pwm_array[4] = kus_min;
  	pwm_array[5] = kus_min;
  } else 
  {
  	pwm_array[4] = kus_max;
	pwm_array[5] = kus_max;
  };
  
  kctrl = delta/koef;
  if(dirctrl == 0) // уменьшаем обороты
  {
	if (pwm_array[2] >= kus_max) zone = 1; else zone = 2;
	kus = pwm_array[zone];
	kus = kus + kctrl;
	if (kus > kus_max) kus = kus_max; 
  };

  if(dirctrl == 1) // увеличиваем обороты
  {
	if (pwm_array[1] <= kus_min) zone = 2; else zone = 1;
	kus = pwm_array[zone];
	kus = kus - kctrl;
	if (kus < kus_min) kus = kus_min;
  };

  pwm_array[zone] = kus;

};
