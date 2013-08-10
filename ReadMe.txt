Saurutobi_Assasin_Costume
=========================

This Repo contains multiple Arduino Projects and libraries aimed at one goal: driving EL wire.
Projects:	-DS18B20_address_finder
			-arduino_ds18b20_temperature_sensor
			-running_costume_with_temp_sensor
			-program_to_test_and_read_freq_for_pwm
			-program_to_test_and_read_temperatures

Libraries:	-DallasTemperature
			-OneWire
			
Each Project and Library has its own purpose.
DS18B20_address_finder:
	This program is designed solely to find the 64bit address of the DS18B20 temperature
	sensors currently connected
	
arduino_ds18b20_temperature_sensor:
	This Project contains sample code on how to use the DS18B20
	
program_to_test_and_read_freq_for_pwm:
	This program is designed to test the EL wire on the El Escudo Dos Arduino sheild to
	find the frequencies where the EL wire does not flicker. The flickering is caused by
	the AC switches in the El Escudo Dos, which wait for the AC wave to peak or Trough.

program_to_test_and_read_temperatures:
	This program was solely designed to find the maximum and minimum temperatures that
	the DS18B20 returns under the costume working environment.

running_costume_with_temp_sensor:
	This is the program that actually runs the Costume. It determines the temperature,
	adjusts the EL wire frequency to a predetermined frequency as found by the testing
	program. This causes the suit to get brighter as you inhale, and dimmer as you
	exhale.

Both libraries are required to allow the DS18B20 to function with any program.

Plans for the Future:
-Add sound sensitivity for different EL wire strands.
-Add heartbeat sensing for different EL wire strands.