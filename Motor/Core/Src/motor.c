#include "motor.h"

void DriveMotor_1(int Steps, int Direction)
{
	HAL_GPIO_WritePin(Dir_1_Port, Dir_1_Pin, Direction);
	for(int i = 0; i < Steps; i++)
	{
		  HAL_GPIO_WritePin(Step_1_Port, Step_1_Pin, SET);
		  HAL_Delay(2);
		  HAL_GPIO_WritePin(Step_1_Port, Step_1_Pin, RESET);
		  HAL_Delay(2);
	}
}

void DriveMotor_2(int Steps, int Direction)
{
	HAL_GPIO_WritePin(Dir_2_Port, Dir_2_Pin, Direction);
	for(int i = 0; i < Steps; i++)
	{
		  HAL_GPIO_WritePin(Step_2_Port, Step_2_Pin, SET);
		  HAL_Delay(2);
		  HAL_GPIO_WritePin(Step_2_Port, Step_2_Pin, RESET);
		  HAL_Delay(2);
	}
}

void DriveMotor_X(int Steps,int Dir)
{
	HAL_GPIO_WritePin(Dir_2_Port, Dir_2_Pin, -Dir);
	HAL_GPIO_WritePin(Dir_1_Port, Dir_1_Pin, Dir);
	for(int i = 0; i < Steps; i++)
	{
		  HAL_GPIO_WritePin(Step_1_Port, Step_1_Pin, SET);
		  HAL_GPIO_WritePin(Step_2_Port, Step_2_Pin, SET);
		  HAL_Delay(2);
		  HAL_GPIO_WritePin(Step_1_Port, Step_1_Pin, RESET);
		  HAL_GPIO_WritePin(Step_2_Port, Step_2_Pin, RESET);
		  HAL_Delay(2);
	}
}

void DriveMotor_Y(int Steps,int Dir)
{
	HAL_GPIO_WritePin(Dir_2_Port, Dir_2_Pin, Dir);
	HAL_GPIO_WritePin(Dir_1_Port, Dir_1_Pin, Dir);
	for(int i = 0; i < Steps; i++)
	{
		  HAL_GPIO_WritePin(Step_1_Port, Step_1_Pin, SET);
		  HAL_GPIO_WritePin(Step_2_Port, Step_2_Pin, SET);
		  HAL_Delay(2);
		  HAL_GPIO_WritePin(Step_1_Port, Step_1_Pin, RESET);
		  HAL_GPIO_WritePin(Step_2_Port, Step_2_Pin, RESET);
		  HAL_Delay(2);
	}

}

