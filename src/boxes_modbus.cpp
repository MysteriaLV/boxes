#include <SimpleModbusSlave.h>

//////////////// registers of BOXES ///////////////////
enum {
	// The first register starts at address 0
			ACTIONS,      // Always present, used for incoming actions

	// Any registered events, denoted by 'triggered_by_register' in rs485_node of Lua script, 1 and up
			MINOR_FAILURE,
	MAJOR_FAILURE,
	COMPLETE,

	TOTAL_ERRORS,     // leave this one, error counter
	TOTAL_REGS_SIZE   // INTERNAL: total number of registers for function 3 and 16 share the same register array
};

unsigned int holdingRegs[TOTAL_REGS_SIZE]; // function 3 and 16 register array
////////////////////////////////////////////////////////////

// Action handler. Add all your actions mapped by action_id in rs485_node of Lua script
void process_actions() {
	if (holdingRegs[ACTIONS] == 0)
		return;

	switch (holdingRegs[ACTIONS]) {
		case 1 : // Put here code for Reset
			Serial.println("[Reset] action fired");
			digitalWrite(LED_BUILTIN, LOW);
			break;
		case 2 : // Put here code for Complete
			Serial.println("[Complete] action fired");
			digitalWrite(LED_BUILTIN, HIGH);
			break;
		default:
			break;
	}

	// Signal that action was processed
	holdingRegs[ACTIONS] = 0;
}

/////////////////////////////////////////////////////////////////

void modbus_setup() {
	Serial.println("Serial ModBus Slave BOXES:2 for lua/Aliens.lua");

	/* parameters(long baudrate,
				  unsigned char ID,
				  unsigned char transmit enable pin,
				  unsigned int holding registers size)
	*/

	modbus_configure(57600, 2, SSerialTxControl, TOTAL_REGS_SIZE);
	holdingRegs[ACTIONS] = 0;
	holdingRegs[MINOR_FAILURE] = 0;
	holdingRegs[MAJOR_FAILURE] = 0;
	holdingRegs[COMPLETE] = 0;
	// Sample calls
	pinMode(LED_BUILTIN, OUTPUT);
	// buttonStatus_setup(MINOR_FAILURE, <buttonPin>);
}


void modbus_loop() {
	holdingRegs[TOTAL_ERRORS] = modbus_update(holdingRegs);
	process_actions();

	// Notify main console of local events
	// holdingRegs[MINOR_FAILURE] = 1;
	// holdingRegs[MAJOR_FAILURE] = 1;
	// holdingRegs[COMPLETE] = 1;


	// Sample calls
	// buttonStatus(MINOR_FAILURE, <buttonPin>);
}
