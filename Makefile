
BOARD_SIZE			?=	2
DROP_PROBABILITY	?=	0

DATASET_DIR		=	dataset
RESULT_TABLE	=	$(DATASET_DIR)/$(BOARD_SIZE)__$(DROP_PROBABILITY).tsv
BUILD_DIR		=	build
APP				=	$(BUILD_DIR)/main.out
OBJS			=	$(BUILD_DIR)/main.o
SRC				=	main.cpp
CARGS			=	-Wall -std=c++14

all: $(APP)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DATASET_DIR):
	mkdir -p $(DATASET_DIR)

$(APP): $(OBJS)
	g++ -o $(APP) $(OBJS)

$(OBJS): $(BUILD_DIR) $(SRC)
	g++ -o $(OBJS) -c $(SRC) $(CARGS)

clean:
	rm -rf $(BUILD_DIR)

clean_full: clean
	rm -rf $(DATASET_DIR)

generate_dataset: $(DATASET_DIR) $(APP)
	mkdir -p $(DATASET_DIR)
	time echo "${BOARD_SIZE} ${DROP_PROBABILITY}"| ./$(APP) > $(RESULT_TABLE)
	@wc -l $(RESULT_TABLE)