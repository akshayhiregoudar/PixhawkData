#include "mavlink_control.h"

int
top (int argc, char **argv)
{
#ifdef __APPLE__
	char *uart_name = (char*)"/dev/tty.usbmodem1";
#else
	char *uart_name = (char*)"/dev/ttyUSB0";
#endif
	int baudrate = 57600;

	parse_commandline(argc, argv, uart_name, baudrate);

	Serial_Port serial_port(uart_name, baudrate);

	Autopilot_Interface autopilot_interface(&serial_port);

	serial_port_quit         = &serial_port;
	autopilot_interface_quit = &autopilot_interface;
	signal(SIGINT,quit_handler);

	serial_port.start();
	autopilot_interface.start();

	commands(autopilot_interface);

	autopilot_interface.stop();
	serial_port.stop();

	return 0;
}



void
commands(Autopilot_Interface &api)
{
    std::ofstream myFile("data.txt");

    for (int i=0; i<100; ++i)
    {
        Mavlink_Messages messages = api.current_messages;
        mavlink_highres_imu_t imu = messages.highres_imu;

        printf("acc_x =  % f, acc_y = %f, acc_z = %f \n", imu.xacc, imu.yacc, imu.zacc); // (m/s^2)
        printf("gyro_x = % f, gyro_y = %f, gyro_z = %f \n", imu.xgyro, imu.ygyro, imu.zgyro); // (rad/s)
        printf("mag_x = % f, mag_y = %f, mag_z = %f \n", imu.xmag, imu.ymag, imu.zmag); // (Ga)

        myFile <<imu.xacc<< std::endl;
        myFile <<imu.yacc<< std::endl;
        myFile <<imu.zacc<< std::endl;
        myFile << imu.xgyro<< std::endl;
        myFile << imu.ygyro<< std::endl;
        myFile << imu.zgyro<< std::endl;
        myFile << imu.xmag<< std::endl;
        myFile << imu.ymag<< std::endl;
        myFile << imu.zmag<< std::endl;

        sleep(1);

     }

}


/*void
commands2(Autopilot_Interface &api)
{
    for (int i=0; i<2; ++i)
    {
        Mavlink_Messages messages2 = api.current_messages;
        mavlink_highres_imu_t imu2 = messages2.highres_imu;

        printf("acc_x =  % f, acc_y = %f, acc_z = %f \n", imu2.xacc, imu2.yacc, imu2.zacc); // (m/s^2)
        printf("gyro_x = % f, gyro_y = %f, gyro_z = %f \n", imu2.xgyro, imu2.ygyro, imu2.zgyro); // (rad/s)
        printf("mag_x = % f, mag_y = %f, mag_z = %f \n", imu2.xmag, imu2.ymag, imu2.zmag); // (Ga)
     }
}*/



        /*void commands(Autopilot_Interface &api)
        {
            /*api.enable_offboard_control();
            usleep(100); // give some time to let it sink in

            mavlink_set_position_target_local_ned_t sp;
            mavlink_set_position_target_local_ned_t ip = api.initial_position;


            api.update_setpoint(sp);


            Mavlink_Messages messages = api.current_messages;

            mavlink_highres_imu_t imu = messages.highres_imu;

            /*int messages_iteration[8] = {1,2,3,4,5,6,7,8};
            int imu_iteration[8] = {1,2,3,4,5,6,7,8};
            for (int i = 1; i <= 8; i++)
            {
                    Mavlink_Messages messages(i) = api.current_messages;
                    mavlink_highres_imu_t imu(i) = messages(i).highres_imu;
                    printf("acc_x =  % f, acc_y = %f, acc_z = %f \n", imu(i).xacc, imu(i).yacc, imu(i).zacc); // (m/s^2)
                    printf("gyro_x = % f, gyro_y = %f, gyro_z = %f \n", imu(i).xgyro, imu(i).ygyro, imu(i).zgyro); // (rad/s)
                    printf("mag_x = % f, mag_y = %f, mag_z = %f \n", imu(i).xmag, imu(i).ymag, imu(i).zmag); // (Ga)

                    sleep(2);
            }


            printf("acc_x =  % f, acc_y = %f, acc_z = %f \n", imu.xacc, imu.yacc, imu.zacc); // (m/s^2)
            printf("gyro_x = % f, gyro_y = %f, gyro_z = %f \n", imu.xgyro, imu.ygyro, imu.zgyro); // (rad/s)
            printf("mag_x = % f, mag_y = %f, mag_z = %f \n", imu.xmag, imu.ymag, imu.zmag); // (Ga)

            //sleep(1);

            //Mavlink_Messages messages2 = api.current_messages;
            //mavlink_highres_imu_t imu2 = messages2.highres_imu;
            //printf("acc_x =  % f, acc_y = %f, acc_z = %f \n", imu2.xacc, imu2.yacc, imu2.zacc); // (m/s^2)
            //printf("gyro_x = % f, gyro_y = %f, gyro_z = %f \n", imu2.xgyro, imu2.ygyro, imu2.zgyro); // (rad/s)
            //printf("mag_x = % f, mag_y = %f, mag_z = %f \n", imu2.xmag, imu2.ymag, imu2.zmag); // (Ga)


            //for (int i = 1; i <= 300000; i++)  // Runtime of 5 minutes (300000 ms)
            //{
                    //mavlink_highres_imu_t imu = messages.highres_imu;

                    //printf("acc_x =  % f, acc_y = %f, acc_z = %f \n", i, imu.xacc, imu.yacc, imu.zacc); // (m/s^2)

                    //printf("gyro_x = % f, gyro_y = %f, gyro_z = %f \n", i, imu.xgyro, imu.ygyro, imu.zgyro); // (rad/s)

                    //printf("mag_x = % f, mag_y = %f, mag_z = %f \n", i, imu.xmag, imu.ymag, imu.zmag); // (Ga)

                    //sleep(2);
            //}


            //fs.open(OutputFile, filename);

            //OutputFile <<"imu.xacc"<< "," <<"imu.yacc"<< "," <<"imu.zacc"<< std::endl;
            //OutputFile <<"imu.xgyro"<< "," <<"imu.ygyro"<< "," <<"imu.zgyro"<< std::endl;
            //OutputFile <<"imu.xmag"<< "," <<"imu.ymag"<< "," <<"imu.zmag"<< std::endl;

            //OutputFile.close();
            std::ofstream myFile("data.csv");

            // Send data to the stream
            /*for(int i = 0; i < 10; ++i)
            {
                Mavlink_Messages messages = api.current_messages;

                mavlink_highres_imu_t imu = messages.highres_imu;

                myFile << imu.xacc<< "," <<imu.yacc<< "," <<imu.zacc<< std::endl;
                myFile << imu.xgyro<< "," <<imu.ygyro<< "," <<imu.zgyro<< std::endl;
                myFile << imu.xmag<< "," <<imu.ymag<< "," <<imu.zmag<< std::endl;
            }

            //myFile << imu.xacc<< "," <<imu.yacc<< "," <<imu.zacc<< std::endl;
            //myFile << imu.xgyro<< "," <<imu.ygyro<< "," <<imu.zgyro<< std::endl;
            //myFile << imu.xmag<< "," <<imu.ymag<< "," <<imu.zmag<< std::endl;


        }


    }
}*/


/*void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int> > > dataset)
{
    // Make a CSV file with one or more columns of integer values
    // Each column of data is represented by the pair <column name, column data>
    //   as std::pair<std::string, std::vector<int>>
    // The dataset is represented as a vector of these columns
    // Note that all columns should be the same size

    // Create an output filestream object
    std::ofstream myFile("data2.csv");

    // Send column names to the stream
    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";

    // Send data to the stream
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }
    // Close the file
    myFile.close();
}*/

//int sendata() {
    // Create an output filestream object
   //std::ofstream myFile("/home/jarv1s/data.csv");

    //Send data to the stream
    //myFile << "imu.xacc\n";
    //myFile << "imu.yacc\n";
    //myFile << "imu.zacc\n";

    // Close the file
    //myFile.close();

    //return 0;
//}


void
parse_commandline(int argc, char **argv, char *&uart_name, int &baudrate)
{

	// string for command line usage
	const char *commandline_usage = "usage: mavlink_serial -d <devicename> -b <baudrate>";

	// Read input arguments
	for (int i = 1; i < argc; i++) { // argv[0] is "mavlink"

		// Help
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
			printf("%s\n",commandline_usage);
			throw EXIT_FAILURE;
		}

		// UART device ID
		if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--device") == 0) {
			if (argc > i + 1) {
				uart_name = argv[i + 1];

			} else {
				printf("%s\n",commandline_usage);
				throw EXIT_FAILURE;
			}
		}

		// Baud rate
		if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--baud") == 0) {
			if (argc > i + 1) {
				baudrate = atoi(argv[i + 1]);

			} else {
				printf("%s\n",commandline_usage);
				throw EXIT_FAILURE;
			}
		}

	}
	// end: for each input argument

	// Done!
	return;
}

void
quit_handler( int sig )
{
	printf("\n");
	printf("TERMINATING AT USER REQUEST\n");
	printf("\n");

	// autopilot interface
	try {
		autopilot_interface_quit->handle_quit(sig);
	}
	catch (int error){}

	// serial port
	try {
		serial_port_quit->handle_quit(sig);
	}
	catch (int error){}

	// end program here
	exit(0);

}


int
main(int argc, char **argv)
{
	// This program uses throw, wrap one big try/catch here
	try
	{
		int result = top(argc,argv);
		return result;
	}

	catch ( int error )
	{
		fprintf(stderr,"mavlink_control threw exception %i \n" , error);
		return error;
        }

}
