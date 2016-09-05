CC := g++-4.8
FLAGS := -std=c++11 -w
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
INCLUDE := -I./$(INC_DIR)

$(BIN_DIR)/Agenda: $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/Agenda.o $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/User.o
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $(INCLUDE) $(BUILD_DIR)/AgendaUI.o $(BUILD_DIR)/Agenda.o $(BUILD_DIR)/AgendaService.o $(BUILD_DIR)/Storage.o $(BUILD_DIR)/Meeting.o $(BUILD_DIR)/Date.o $(BUILD_DIR)/User.o -o $@

$(BUILD_DIR)/Agenda.o: $(SRC_DIR)/Agenda.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/Agenda.cpp

$(BUILD_DIR)/AgendaUI.o: $(SRC_DIR)/AgendaUI.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/AgendaUI.cpp

$(BUILD_DIR)/AgendaService.o: $(SRC_DIR)/AgendaService.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/AgendaService.cpp

$(BUILD_DIR)/Storage.o: $(SRC_DIR)/Storage.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/Storage.cpp

$(BUILD_DIR)/Meeting.o: $(SRC_DIR)/Meeting.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/Meeting.cpp

$(BUILD_DIR)/Date.o: $(SRC_DIR)/Date.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/Date.cpp

$(BUILD_DIR)/User.o: $(SRC_DIR)/User.cpp 
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INCLUDE) -c -o $@ $(SRC_DIR)/User.cpp


clean:
	@rm -f main
	@rm -f *.o
	@rm -f *.gch

	@rm -rf $(BUILD_DIR)
	@rm -rf $(BIN_DIR)
