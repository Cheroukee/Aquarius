#include "Atlas_I2C_DO.h"

namespace aquarius
{
	
    int Atlas_I2C_DO::command_Calibration(string parameter, string value)
    {
        string returnString;
        string command;
        int type = -1;
        
        if(value.compare(NO_CALIBRATION_VALUE) == 0 && 
                ( parameter.compare(PH_COMMAND_CLEAR) == 0 || 
                    parameter.compare(I2C_COMMAND_ARG_QUEST) == 0))
        {
           command = (string)I2C_COMMAND_CALIB + I2C_DELIMITER + parameter;
           type = 0;
        }
        else if(value.compare(NO_CALIBRATION_VALUE) != 0 && 
                 ( parameter.compare(PH_COMMAND_MID) == 0 || 
                    parameter.compare(PH_COMMAND_HIGH) == 0 || 
                        parameter.compare(PH_COMMAND_LOW) == 0))
        {
            command = (string)I2C_COMMAND_CALIB + I2C_DELIMITER + parameter + I2C_DELIMITER + value;
            type = 1;
        }
        
        int commandResult = aquarius::i2cCommand(i2c_,command, I2C_COMMAND_CALIB_DELAY, &returnString);
        
        if(commandResult == I2C_READ_BACK_OK)
    	{
    	    if(type)
    		    aquarius::outputCommandResult(deviceName_, (string)CALIBRATION_SUCCESSFULL_P1 + value + CALIBRATION_SUCCESSFULL_P2 + parameter);
    		else
    		    aquarius::outputCommandResult(deviceName_, (string)CALIBRATION_QUERIED + splitArguments(returnString, ',')[1]);
    	}
    	else if(commandResult == I2C_READ_BACK_FAIL)
    		aquarius::outputError(deviceName_, I2C_READ_FAIL);
    	else if(commandResult == I2C_READ_BACK_PENDING)
    		aquarius::outputError(deviceName_, I2C_READ_PENDING);
    	else if(commandResult == I2C_READ_BACK_NO_DATA)
    		aquarius::outputError(deviceName_, I2C_READ_NO_DATA);
		else
    	    aquarius::outputError(deviceName_, I2C_COMMS_ERROR);
    	    
        return commandResult;
    }
    
    int Atlas_I2C_DO::command_Reading()
    {
        string returnString;
        int commandResult = aquarius::i2cCommand(i2c_, I2C_COMMAND_R, I2C_COMMAND_R_DELAY, &returnString);
        
    	if(commandResult == I2C_READ_BACK_OK)
    	{
    		string dataName[] = { ATLAS_DO_DATA_1,  ATLAS_DO_DATA_2};
    		
    		string tempPrct = returnString.substr(1);
			string tempDO;
    		
    		float datas[] = { (float)atof(tempPH.c_str()) };
    		
    		aquarius::outputReadData(deviceName_, ATLAS_DO_DATA_QTY, dataName, datas);
    	}
    	else if(commandResult == I2C_READ_BACK_FAIL)
    	{
    		aquarius::outputError(deviceName_, I2C_READ_FAIL);
    	}
    	else if(commandResult == I2C_READ_BACK_PENDING)
    	{
    		aquarius::outputError(deviceName_, I2C_READ_PENDING);
    	}
    	else if(commandResult == I2C_READ_BACK_NO_DATA)
    	{
    		aquarius::outputError(deviceName_, I2C_READ_NO_DATA);
    	}
		else
    	{
    	    aquarius::outputError(deviceName_, I2C_COMMS_ERROR);
    	}
		return commandResult;
    }
	
	int Atlas_I2C_DO::command_Output_String_Config(string parameter, string enable = NO_CALIBRATION_VALUE)
	{
		string returnString;
		string command = (string)DO_COMMAND_O + I2C_DELIMITER + parameter;
		int setting = 0;
		if(enable.compare(NO_CALIBRATION_VALUE) != 0)
		{
			command += (string)I2C_DELIMITER + enable;	
			setting++;
		}
		int commandResult = aquarius::i2cCommand(i2c_, command, DO_COMMAND_O_DELAY, &returnString);
		
		if(commandResult == I2C_READ_BACK_OK)
    	{
			if(setting)
			{
				aquarius::outputCommandResult(deviceName_, (string)DO_OUTPUT_SET_AT + enable);
			}
			else
			{
				aquarius::outputCommandResult(deviceName_, (string)DO_OUTPUT_IS_AT + returnString);
			}
    	}
    	else if(commandResult == I2C_READ_BACK_FAIL)
    	{
    		aquarius::outputError(deviceName_, I2C_READ_FAIL);
    	}
    	else if(commandResult == I2C_READ_BACK_PENDING)
    	{
    		aquarius::outputError(deviceName_, I2C_READ_PENDING);
    	}
    	else if(commandResult == I2C_READ_BACK_NO_DATA)
    	{
    		aquarius::outputError(deviceName_, I2C_READ_NO_DATA);
    	}
		else
    	{
    	    aquarius::outputError(deviceName_, I2C_COMMS_ERROR);
    	}
		return commandResult;
	}
			
	int Atlas_I2C_DO::command_Pressure(string parameter)
	{
		string returnString;
        int commandResult = aquarius::i2cCommand(i2c_, DO_COMMAND_P, DO_COMMAND_P_DELAY, &returnString);
        
        if(commandResult == I2C_READ_BACK_OK)
    	{
		    if(parameter.compare(I2C_COMMAND_ARG_QUEST) == 0)
                aquarius::outputCommandResult(deviceName_, (string)DO_COMPENSATION_PRESSURE + splitArguments(returnString, ',')[1]);
            else
                aquarius::outputCommandResult(deviceName_, (string)DO_COMPENSATION_SET_PRESSURE + parameter);
    	}
    	else if(commandResult == I2C_READ_BACK_FAIL)
    		aquarius::outputError(deviceName_, I2C_READ_FAIL);
    	else if(commandResult == I2C_READ_BACK_PENDING)
    		aquarius::outputError(deviceName_, I2C_READ_PENDING);
    	else if(commandResult == I2C_READ_BACK_NO_DATA)
    		aquarius::outputError(deviceName_, I2C_READ_NO_DATA);
		else
    	    aquarius::outputError(deviceName_, I2C_COMMS_ERROR);
    	return commandResult;
	}
	
	int Atlas_I2C_DO::command_Salinity(string parameter)
	{
		string returnString;
        int commandResult = aquarius::i2cCommand(i2c_, DO_COMMAND_S, DO_COMMAND_S_DELAY, &returnString);
        
        if(commandResult == I2C_READ_BACK_OK)
    	{
		    if(parameter.compare(I2C_COMMAND_ARG_QUEST) == 0)
                aquarius::outputCommandResult(deviceName_, (string)DO_COMPENSATION_SALINITY + splitArguments(returnString, ',')[1]);
            else
                aquarius::outputCommandResult(deviceName_, (string)DO_COMPENSATION_SET_SALINITY + parameter);
    	}
    	else if(commandResult == I2C_READ_BACK_FAIL)
    		aquarius::outputError(deviceName_, I2C_READ_FAIL);
    	else if(commandResult == I2C_READ_BACK_PENDING)
    		aquarius::outputError(deviceName_, I2C_READ_PENDING);
    	else if(commandResult == I2C_READ_BACK_NO_DATA)
    		aquarius::outputError(deviceName_, I2C_READ_NO_DATA);
		else
    	    aquarius::outputError(deviceName_, I2C_COMMS_ERROR);
    	return commandResult;		
	}	
}