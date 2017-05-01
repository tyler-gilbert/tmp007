#include <cstdio>
#include <stfy/hal.hpp>
#include <stfy/sys.hpp>
#include <stfy/var.hpp>

int main(int argc, char * argv[]){
	I2C i2c(1);
	String command;
	u16 temp_value;
	u16 temp_value_le;

	i2c.init(100000);
	i2c.setup(0x40);

	printf("Start\n");

	do {
		command.clear();
		if( fgets(command.cdata(), command.capacity(), stdin) != 0 ){
			if( command == "read\n" ){
				temp_value = 0x0F88;
				if( i2c.read(3, &temp_value, 2) == 2 ){
					temp_value_le = (temp_value >> 8) | ((temp_value & 0xFF) << 8);
					printf("%0.2f\n", temp_value_le * 0.03125 / 4);
				} else {
					printf("error\n");
				}
			}
		}
	} while( command != "exit\n" );

	printf("done\n");


	return 0;
}
