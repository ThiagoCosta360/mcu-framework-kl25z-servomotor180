/*!
 * @copyright   © 2020 UFAM - Universidade Federal do Amazonas.
 *
 * @brief       Implementação da classe "mkl_ServoMotor180".
 *
 * @file        mkl_ServoMotor180.cpp
 * @version     1.0
 * @date        20 Janeiro 2020
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +compiler     Kinetis� Design Studio IDE.
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012.
 *              +revisions    Versão (data): Descrição breve.
 *                             ++ 1.0 (20 Janeiro 2020): Versão inicial.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Universidade Federal do Amazonas.
 *              +courses      Engenharia da Computação / Engenharia Elétrica.
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Versão inicial:
 *                             ++ Thiago Costa Antunes Afonso <tcaa@icomp.ufam.edu.br>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              Este programa é um software livre; Você pode redistribuí-lo
 *              e/ou modificálo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              versão 3 da licença, ou qualquer versão posterior.
 *
 *              Este programa é distribuído na esperança de que seja útil,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia implícita de
 *              COMERCIALIZA��O OU USO PARA UM DETERMINADO PROPÓSITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */


#include "mkl_ServoMotor180.h"
#include "mkl_TPMPulseWidthModulation.h"
#include "stdio.h"

/*!
 *   @fn         ServoMotor180.
 *
 *   @brief      Construtor padrão da classe mkl_TPMPulseWidthModulation.
 *
 *   Este método é o construtor padrão da classe, que realiza a o controle
 *   periférico servo motor de 180 graus. O construtor inicia o motor na posição 0.
 *
 *   @param[in]  tpmPin - pino de saída do sinal PWM gerado para o motor.
 *
 */
    mkl_ServoMotor180::mkl_ServoMotor180(tpm_Pin tmpPin) : pwmServoMotor(tmpPin)
    {
    	//Ajusta a Frequência do PWM para 50Hz ( T = 20ms )
    	pwmServoMotor.setFrequency(tpm_div8, 52427);

		pulseWidthMin =  0.45;
		pulseWidthMax =  2.55;

    	writeAngle(0);
    }

/*!
 *   @fn         turnOn.
 *
 *   @brief     Habilita o sinal PWM.
 *
 *   Este método é utilizado como interface ao enableOperation
 *   da classe mkl_TPMPulseWidthModulation
 *
 */
    void mkl_ServoMotor180::turnOn()
    {
    	pwmServoMotor.enableOperation();
    }



	void mkl_ServoMotor180::setPWM(double pwmMin, double pwmMax){

	   pulseWidthMin = pwmMin;
	   pulseWidthMax = pwmMax;

	}

/*!
 *   @fn		turnOff.
 *
 *   @brief		Desabilita o sinal PWM.
 *
 *   Este método é utilizado como interface ao disableOperation
 *   da classe mkl_TPMPulseWidthModulation
 *
 */
    void mkl_ServoMotor180::turnOff()
    {
    	pwmServoMotor.disableOperation();
    }

/*!
 *   @fn         writeAngle.
 *
 *   @brief      Ajusta o duty cycle do PWM com base no ângulo do motor.
 *
 *   Este método ajusta o duty cycle considerando a seguinte express�o:
 *   duty_cycle = ((angle*17)/9 + 80) que serve basicamente para mapear os
 *   valores de angulo que variam de 0 a 180 em valores de duty_cyclo que
 *   variam de 80 á 420.
 *
 *	 O valores do divBase e MODRegister foram calculados de tal forma que
 *	 a frequencia resultante seja 50Hz, como exigido pelo motor.
 *
 *   @param[in]  angle - Valor desejado para a posição relativa da haste do motor.
 *
 */
    void mkl_ServoMotor180::writeAngle(int angle){
    	// duty = 1048 + ((7340 - 1048)* angle) / 180;
      duty = (pulseWidthMin*52427)/20 + (((pulseWidthMax*52427)/20 - (pulseWidthMin*52427)/20)* angle) / 180;

    	pwmServoMotor.setDutyCycle(duty);
    	turnOn();

    }
