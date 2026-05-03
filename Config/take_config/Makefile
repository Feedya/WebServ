C++ = c++
C++_FLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic
#------------------------------------------------------------------
#DIRECTION - DIRECTION - DIRECTION - DIRECTION - DIRECTION
TAKE_CONFIG_DIR = take_config

TEST_FILENAME_DIR = take_config/test_filename

READ_FILE_CONFIG_DIR = read_file_config

#------------------------------------------------------------------
#FICHIER SOURCE - FICHIER SOURCE - FICHIER SOURCE - FICHIER SOURCE
TAKE_CONFIG_SRC = $(TAKE_CONFIG_DIR)/take_config.cpp

TEST_FILENAME_SRC = $(TEST_FILENAME_DIR)/compare_end.cpp $(TEST_FILENAME_DIR)/see_if_exist.cpp\
					$(TEST_FILENAME_DIR)/test_filename.cpp

READ_FILE_CONFIG_SRC = $(READ_FILE_CONFIG_DIR)/read_file_config.cpp

#------------------------------------------------------------------

INFILES = 	main.cpp $(TAKE_CONFIG_SRC) $(TEST_FILENAME_SRC) $(READ_FILE_CONFIG_SRC)
#------------------------------------------------------------------

OBJFILES = $(INFILES:.cpp=.o)

NAME = web

all: $(NAME)

$(NAME):$(OBJFILES)
	$(C++) $(C++_FLAGS) $(OBJFILES) -o $(NAME) 

%.o: %.cpp
	$(C++) $(C++_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re