#include "GraphicsParser.hpp"

GraphicsParser::GraphicsParser() {
    current_max_id = 0;
}

void GraphicsParser::switch_session(int session_id) {
    current_session = &sessions[session_id - 1];
    std::cout << "You switched to session with ID: " << session_id << std::endl;
    current_session->session_info();
}

void GraphicsParser::run() {
    while(true) {
        char buffer[256];
        std::cout << "> ";
        std::cin.getline(buffer, 256);
        Vector<String> command = String(buffer).split(' ');
        if(command[0] == "load") {
            load(String(buffer));
        } 
        else if(command[0] == "close") {

        }
        else if(command[0] == "save") {
            current_session->save();
        }
        else if(command[0] == "saveas") {
            Vector<String> file_names;
            for(int i = 1; i < command.get_size(); i++) {
                file_names.add_element(command[i]);
            }
            current_session->save_as(file_names);
        }
        else if(command[0] == "help") {
            help();
        }
        else if(command[0] == "exit") {
            return;
        }
        else if(command[0] == "monochrome" || command[0] == "grayscale" || command[0] == "negative" || command[0] == "rotate") {
            current_session->add_command(String(buffer));
        }
        else if(command[0] == "undo") {
            current_session->undo();
        }
        else if(command[0] == "add") {
            String file_name = command[1];
            int pos = 0;
            while(file_name[pos] != '.' && file_name[pos] != '\0') {
                pos++;
            }
            if(pos > 0 && !strcmp(&file_name[pos], ".pbm") && !strcmp(&file_name[pos], ".ppm") && !strcmp(&file_name[pos], ".pgm")) {
                std::fstream image_file;
                image_file.open(file_name.to_cstr(), std::ios::out | std::ios::app);
                image_file.close();
                image_file.open(file_name.to_cstr(), std::ios::in);
                if(image_file) {
                    String format;
                    image_file >> format;
                    if(format == "P1" || format == "P4") {
                        Graphics* bitmap = new Bitmap(0, 0, format);
                        bitmap->read(image_file);
                        current_session->add(bitmap);
                        current_session->add_file(file_name);
                    }
                    else if(format == "P2" || format == "P5") {
                        Graphics* graymap = new Graymap(0, 0, format);
                        graymap->read(image_file);
                        current_session->add(graymap);
                        current_session->add_file(file_name);
                    }
                    else if(format == "P3" || format == "P6") {
                        Graphics* pixmap = new Pixmap(0, 0, format);
                        pixmap->read(image_file);
                        current_session->add(pixmap);
                        current_session->add_file(file_name);
                    }
                    else {
                        std::cout << "Image invalid!" << std::endl;
                        return;
                    } 
                }
                image_file.close();        
            }
            std::cout << "Image " << file_name << " added" << std::endl;
        }
        else if(String(buffer) == "session info") {
            current_session->session_info();
        }
        else if(command[0] == "switch") {
            switch_session(command[1].to_int());
        } 
        else if(command[0] == "collage") {
            Graphics* image1 = current_session->find_image(command[2]);
            Graphics* image2 = current_session->find_image(command[3]);
            Graphics* outimage; 
            if(image1->get_format() != image2->get_format()) {
                std::cout << "Cannot make a collage from different types! (" << image1->get_format() << " and " << image2->get_format() << ")" << std::endl;
                return;
            }
            if(image1->get_format() == "P1" || image1->get_format() == "P4") {
                outimage = new Bitmap(image1->get_rows(), image1->get_columns(), image1->get_format()); 
            }
            else if(image1->get_format() == "P2" || image1->get_format() == "P5") {
                outimage = new Graymap(image1->get_rows(), image1->get_columns(), image1->get_format());
            }
            else if(image1->get_format() == "P3" || image1->get_format() == "P6") {
                outimage = new Pixmap(image1->get_rows(), image1->get_columns(), image1->get_format());
            }
            outimage->set_image(image1->get_image());
            outimage->set_max_value(image1->get_max_value());
            if(command[1] == "horizontal") {
                outimage->append_horizontally(image2);
            }
            else if(command[1] == "vertical") {
                outimage->append_vertically(image2);
            }
            current_session->add(outimage);
            current_session->add_file(command[4]);
            std::cout << "New collage \"" << command[4] << "\" created" << std::endl; 
        }
    }   
}

void GraphicsParser::load(String command) {
    Vector<String> command_split = command.split(' ');
    Vector<Graphics*> images;
    Vector<String> file_names;
    for(int i = 1; i < command_split.get_size(); i++) {
        String file_name = command_split[i];
        int pos = 0;
        while(file_name[pos] != '.' && file_name[pos] != '\0') {
            pos++;
        }
        if(pos > 0 && (!strcmp(&file_name[pos], ".pbm") || !strcmp(&file_name[pos], ".pgm") || !strcmp(&file_name[pos], ".ppm"))) {
            std::fstream image_file;
            image_file.open(file_name.to_cstr(), std::ios::out | std::ios::app);
            image_file.close();
            image_file.open(file_name.to_cstr(), std::ios::in);
            if(image_file) {
                String format;
                image_file >> format;
                if(format == "P1" || format == "P4") {
                    Graphics* bitmap = new Bitmap(0, 0, format);
                    bitmap->read(image_file);
                    images.add_element(bitmap);
                    file_names.add_element(file_name);
                }
                else if(format == "P2" || format == "P5") {
                    Graphics* graymap = new Graymap(0, 0, format);
                    graymap->read(image_file);
                    images.add_element(graymap);
                    file_names.add_element(file_name);
                }
                else if(format == "P3" || format == "P6") {
                    Graphics* pixmap = new Pixmap(0, 0, format);
                    pixmap->read(image_file);
                    images.add_element(pixmap);
                    file_names.add_element(file_name);
                }
                else {
                    std::cout << "Image invalid!" << std::endl;
                    return;
                } 
            }
            image_file.close();
        }
        else {
            std::cout << "That's invalid" << std::endl;
            return;
        }
    }
    current_max_id++;
    Session session(images, file_names, current_max_id); 
    sessions.add_element(session);
    current_session = &sessions[sessions.get_size() - 1];
    std::cout << "Session with ID: " << current_max_id << " started" << std::endl;
    for(int i = 0; i < file_names.get_size(); i++) {
        std::cout << "Image \"" << file_names[i] << "\" added" << std::endl;
    }
}

void GraphicsParser::close() {

}

void GraphicsParser::help() {
    std::cout << "The following commands are supported:\nopen <file>    opens <file>\nclose            closes currently opened file\nsave            saves the currently open file\nsaveas <file>    saves the currently open file in <file>\nhelp            prints this information\nexit            exists the program" << std::endl;
}
