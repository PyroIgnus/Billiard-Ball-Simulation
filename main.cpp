/****************************************************/
/**                                                **/
/**      Jonathon Wong                             **/
/**      998823698                                 **/
/**      CSC444                                    **/
/**      Assignment 1: Billiard Ball Simulation    **/
/**      Last updated October 6, 2013              **/
/**                                                **/
/****************************************************/

#include <iostream>
#include <string.h>
#include "utils.h"
#include "BilliardTable.h"

using namespace std;

int main()
{

    bool exit = false;
    char fileName[150];
    BilliardTable table = *new BilliardTable(0, 0);

    while (!exit) {
        cout << "Enter the name of the input file (type exit to end session): ";
        std::cin.getline(fileName, 150 - 2);
        if (fileName == NULL || strcmp(fileName, "") == 0) {
            cout << "Invalid input.  Please try again." << endl;
        }
        else if (strcmp(fileName, "exit") == 0) {
            exit = true;
        }
        else {
            cout << "Loading..." << endl;
            // Attempt to load the new table.
            if (!table.initialize(fileName)) {
                cout << "Error reading file " << fileName << ".  Please try again." << endl;
            }
            else {
                cout << "Finished loading file" << endl;
                cout << "Calculating..." << endl;
                // Carry out simulation.
                while (table.getNumActive() > 0) {
                    table.update();
                }
                // Load results into output file.
                char temp[150];
                strncpy(temp, fileName, strlen(fileName) - 4);
                temp[strlen(fileName) - 4] = '\0';
                strcat(temp, "_o.txt"); // Append "_o" to the end of the file name.
                cout << "Outputting results to " << temp << endl;
                FILE* out = fopen(temp, "w");   // Overwrites file if it already exists.
                if (out == NULL) {
                    cout << "Error opening/writing to output file." << endl;
                }
                else {
                    // Start writing lines to the file.
                    fprintf(out, "%f %f\n", table.getWidth(), table.getHeight());
                    for (int i = 0; i < table.getNumBalls(); i++) {
                        Ball b = table.getBall(i);
                        fprintf(out, "%f %f %f %f\n", b.getPos().getX(), b.getPos().getY(), b.getSpeed().getX(), b.getSpeed().getY());
                    }
                    cout << "Finished output." << endl;
                }

                strcpy (fileName, "");
            }
        }
    }

    cout << "Finished." << endl;
    return 0;
}
