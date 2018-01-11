/************************************************************/
/* This file is to optimize the code for repeated operations*/
/************************************************************/

#include "AgilisAppUtil.h"

/*********************************************************/
/* This function is to validate the attenutation value   */
/*					for its limits                       */
/*********************************************************/

void AgilisAppUtil_validate_attenuation(BUCinfo_t * buc_info)
{

  if ((buc_info->operation.usrSetAttn*10)>300)
	  {
        buc_info->operation.usrSetAttn=30;
   	  }
  if ((buc_info->operation.usrSetAttn*10)<0)
	  {
		buc_info->operation.usrSetAttn=0;
	  }
}


DWORD AgilisAppUtil_dword_swap(DWORD val)
{
	 return(DWORD)(((val<<24ul)&0xff000000)
			      |((val<<8ul)&0x00ff0000)
				  |((val>>8ul)&0x0000ff00)
				  |((val>>24ul)&0x000000ff));
}



BYTE* Agilis_util_convert_ascii(DWORD value)
{
	int remain;
	
	memset(global_char_temp, 0 , sizeof(global_char_temp));
	
	remain = value % 10;

    value /= 10;

	uitoa(value, (BYTE*)global_char_temp);

	if(remain != 0 )
	{
		strcatpgm2ram(global_char_temp,".");
		strcatpgm2ram(global_char_temp,"5");
	}
	else
	{
		strcatpgm2ram(global_char_temp,".");
		strcatpgm2ram(global_char_temp,"0");
	}

  return (&global_char_temp);
}




float Agilis_util_parse_attn(BYTE *ptr)
{ 
   char k;
   BYTE attn[7]={0};
   	
	for(k=0;k<6;k++)
	{
		attn[k]=*(ptr+k);
	}

	if((*ptr<0x30)||(*ptr>0x39))
	{
	 	return 0xFF;
	}
    for(k=0;k<5;k++)
    {
      if((*(ptr+k)=='.')&&(*(ptr+k+1)!='5')&&(*(ptr+k+1)!='0'))
      {
         return 0xFF;
      }
    }
  return (atof5(attn));
}
