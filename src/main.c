#include "address_book.h"

int main() 
{       
        init_book();

        do {
                show_menu();
                unsigned decision = get_menu_input();
                choose_option(decision);
                program_should_close();
        } while (is_program_opened());

        delete_all_addresses();
        return 0;
}