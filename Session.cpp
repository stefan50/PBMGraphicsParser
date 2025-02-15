#include "Session.hpp"

Session::Session(Vector<Graphics*> images, Vector<String> file_names, int id) {
    this->id = id;
    for(int i = 0; i < images.get_size(); i++) {
        this->images.add_element(images[i]);
        this->file_names.add_element(file_names[i]);
    }
}

void Session::add(Graphics* image) {
    images.add_element(image);
}

void Session::add_file(String file) {
    file_names.add_element(file);
}

void Session::session_info() {
    std::cout << "Name of images in the session: ";
    for(int i = 0; i < file_names.get_size(); i++) {
        std::cout << file_names[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Pending transformations: ";
    for(int i = 0; i < commands.get_size(); i++) {
        std::cout << commands[i] << " ";
    }
    std::cout << std::endl;
}

void Session::add_command(String command) {
    commands.add_element(command);
}

void Session::undo() {
    commands.remove_last_element();
}

void Session::grayscale() {
    for(int i = 0; i < images.get_size(); i++) {
        images[i]->grayscale();
    }
}

void Session::monochrome() {
    for(int i = 0; i < images.get_size(); i++) {
        images[i]->monochrome();
    }
}

void Session::negative() {
    for(int i = 0; i < images.get_size(); i++) {
        images[i]->negative();
    }
}

void Session::rotate(String direction) {
    for(int i = 0; i < images.get_size(); i++) {
        images[i]->rotate(direction);
    }
}

void Session::save_as(Vector<String> file_names) {
    /*if(this->file_names.get_size() != file_names.get_size()) {
        return;
    }*/
    for(int i = 0; i < commands.get_size(); i++) {
        Vector<String> command_split = commands[i].split(' ');
        if(command_split[0] == "grayscale") {
            grayscale();
        } 
        else if(command_split[0] == "monochrome") {
            monochrome();
        }
        else if(command_split[0] == "negative") {
            negative();
        }
        else if(command_split[0] == "rotate") {
            rotate(command_split[1]);
        }
        /*else if(command_split[0] == "collage") {
            int pos_file1 = 0, pos_file2 = 0;
            while(file_names[pos_file1] != command_split[2]) {
                pos_file1++;
            }
            while(file_names[pos_file2] != command_split[3]) {
                pos_file2++;
            }
            collage(command_split[1], images[pos_file1], images[pos_file2], command_split[4]);
        }*/
    }
    int size = commands.get_size();
    for(int i = 0; i < size; i++) {
        commands.remove_last_element();
    }
    for(int i = 0; i < file_names.get_size(); i++) {
        std::ofstream out(file_names[i].to_cstr());
        images[i]->write(out);
        out.close();
    }
} 

void Session::save() {
    save_as(file_names);
}

void Session::collage(String direction, Graphics* image1, Graphics* image2, String outimage) {
    Graphics* out_image = image1;
    if(direction == "horizontal") {
        out_image->append_horizontally(image2);
    }
    else if(direction == "vertical") {
        out_image->append_vertically(image2);
    }
    images.add_element(out_image);
    file_names.add_element(outimage);
}
