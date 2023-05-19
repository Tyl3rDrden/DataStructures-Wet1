#include <iostream>
#include "StreamingDBa1.h"

int main()
{
    streaming_database db;
    // Adding movies to the database
    //db.add_movie(1, Genre::ACTION, 100, false);
    //db.add_movie(2, Genre::ACTION, 200, true);
    //db.add_movie(3, Genre::COMEDY, 150, false);
    //db.add_movie(4, Genre::COMEDY, 250, true);
    /*
    // Adding users to the database
    db.add_user(1, true);
    db.add_user(2, false);

    // Removing a movie
    StatusType status = db.remove_movie(2);
    if (status == StatusType::SUCCESS)
        std::cout << "Movie removed successfully" << std::endl;
    else
        std::cout << "Failed to remove movie" << std::endl;

    // Removing a user
    status = db.remove_user(1);
    if (status == StatusType::SUCCESS)
        std::cout << "User removed successfully" << std::endl;
    else
        std::cout << "Failed to remove user" << std::endl;
    
    // Testing movie count by genre
    auto movieCount = db.get_all_movies_count(Genre::ACTION);
    if (movieCount.status == StatusType::SUCCESS)
        std::cout << "Movie count: " << movieCount.value << std::endl;
    else
        std::cout << "Failed to get movie count" << std::endl;

    // Assuming output is an array of sufficient size
    int output[10];
    status = db.get_all_movies(Genre::ACTION, output);
    if (status == StatusType::SUCCESS)
    {
        std::cout << "Movies in Action genre: ";
        for (int i = 0; i < 10; i++)
        {
            std::cout << output[i] << " ";
        }
        std::cout << std::endl;
    }
    else
        std::cout << "Failed to get movies" << std::endl;
    */
    return 0;
}