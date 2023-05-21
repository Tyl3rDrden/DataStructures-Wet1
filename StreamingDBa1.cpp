#include "StreamingDBa1.h"

streaming_database::streaming_database()
{
    //Let's make the AVL Tree's need and change them ad hoc
    // TODO: Your code goes here

    //Creating Trees of Movies Ranked By Genre!

    //making an array of AVL TREES!
    AVLTREE<Movie, CompareMovieStatisticsFunctor, int>* movieTreesArray = new AVLTREE<Movie, CompareMovieStatisticsFunctor, int>[NUMBEROFGENRES];

    //m_GenreAVLtreesPtr = new AVLTREE<Movie, CompareMovieStatisticsFunctor, Movie::Statistics>[NUMBEROFGENRES];
    //More Avl Trees By statistics
}

streaming_database::~streaming_database()
{
    /*for (int i = 0; i < NUMBEROFGENRES; i++)
    {
        m_GenreAVLtreesPtr[i].~AVLTREE();
        //Calling the Destructors
    }*/
    //delete[] m_GenreAVLtreesPtr;


    //Just call the destructors of all the avl trees..


    // TODO: Your code goes here
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    //Check Arguments:
    if(movieId <= 0 || genre == Genre::NONE || views <0)
    {
        return StatusType::INVALID_INPUT;
    }
    //I'd rather check the Id before allocating Nodes.. It's probably going to be faster
    try
    {

        if(!m_moviesbyId.ElementInTree(movieId))
        {//Returns False if cannot find the movie By id !
            std::shared_ptr<Movie> newMoviePtr = std::make_shared<Movie>(movieId, genre, views, vipOnly);
            m_moviesbyId.InsertElement(newMoviePtr, newMoviePtr->getMovieIdPtr());
            int GenreNum = static_cast<int>(genre);
            //Converting Genre To it's corresponding int
            std::shared_ptr<Movie> copyPtr(newMoviePtr);
            //Making a new sharedpointer using hte copy constructor
            m_GenreAVLtreesPtr[GenreNum].InsertElement(copyPtr, copyPtr->getStatisticsPtr());
        }
        else
        {
            return StatusType::FAILURE;
        }
    } catch (const std::bad_alloc& ex)
    {
        //std::cout << "Caught Bad Allocation exception: " << ex.what() << std::endl;
        return StatusType::ALLOCATION_ERROR;
    }
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId <= 0)
    {
        return StatusType::INVALID_INPUT;

    }
    else if(!m_moviesbyId.ElementInTree(movieId))
    {
        //No movie Exists
        return StatusType::FAILURE;
    }
    try
    {
        std::shared_ptr<Movie> remMovie  = m_moviesbyId.FindandGetSharedPtr(movieId);
        Movie::Statistics statsKey = remMovie->getStatistics();
        int remGenre = static_cast<int>(remMovie->getGenre());
        m_GenreAVLtreesPtr[remGenre].RemoveElement(remMovie->getStatistics());
        //m_GenreAVLtreesPtr[1].RemoveElement(remMovie.getStatistics());

        m_moviesbyId.RemoveElement(movieId);
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;

    //Remove movie from GenreAvlTree



    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
    if(userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(m_usersbyId.ElementInTree(userId))
    {
        return StatusType::FAILURE;
    }
    try
    {
        std::shared_ptr<User> newUserPtr = std::make_shared<User>(userId, isVip);
        m_usersbyId.InsertElement(newUserPtr, &(newUserPtr->getId()));
        //GetId is suppost to return A refrence Here
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    //Create using makeshred

    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    if(userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(!m_usersbyId.ElementInTree(userId))
    {
        return StatusType::FAILURE;
    }
    try
    {
        std::shared_ptr<User> remUser = m_usersbyId.FindandGetSharedPtr(userId);

        if(remUser->inGroup())
        {
            (remUser->getGroupPtr())->deleteUser(userId);
            //Remove the user from the group
        }
        m_usersbyId.RemoveElement(userId);
        //GetId is suppost to return A refrence Here
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
    //Check is user is part of a group.


    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(m_groupsbyId.ElementInTree(groupId))
    {
        return StatusType::FAILURE;
    }
    try
    {

        std::shared_ptr<Group> newGroupPtr = std::make_shared<Group>(groupId);
        m_groupsbyId.InsertElement(newGroupPtr, &(newGroupPtr->getId()));

        //GetId is suppost to return A refrence Here
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    //Easy
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
    if(groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(!m_groupsbyId.ElementInTree(groupId))
    {
        return StatusType::FAILURE;
    }
    try
    {

        m_groupsbyId.RemoveElement(groupId);
        //The rest of the implementation is in the destructor of Group!;
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    //Easy
    // TODO: Your code goes here
    return StatusType::SUCCESS;
    //Just Remove it from the tree!
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if(groupId <= 0 || userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(!m_groupsbyId.ElementInTree(groupId)  || !m_usersbyId.ElementInTree(userId))
    {
        return StatusType::FAILURE;
    }
    try
    {
        std::shared_ptr<Group> group = m_groupsbyId.FindandGetSharedPtr(groupId);
        std::shared_ptr<User> user = m_usersbyId.FindandGetSharedPtr(userId);
        if(user->inGroup())
        {
            return StatusType::FAILURE;
        }

        group->addUser(user);

        //GetId is suppost to return A refrence Here


        //The group Destructor is getting called here For some reason
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    //Easy
    // TODO: Your code goes here
    return StatusType::SUCCESS;
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if(movieId <= 0 || userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(!m_moviesbyId.ElementInTree(movieId)  || !m_usersbyId.ElementInTree(userId))
    {
        return StatusType::FAILURE;
    }
    try
    {
        std::shared_ptr<Movie> movie = m_moviesbyId.FindandGetSharedPtr(movieId);
        std::shared_ptr<User> user = m_usersbyId.FindandGetSharedPtr(userId);
        if(!user->isVip() && movie->getVipOnly())
        {
            return StatusType::FAILURE;
        }
        if(user->inGroup())
        {
            (user->getGroupPtr())->incrementSumGenreCount(movie->getGenre());

            //Potential Mistake

            //If user is part of a group then increment the Groups Views!
        }
        //User increments His own Counter
        user->incrementViewsbyGenre(movie->getGenre());
        //GetId is suppost to return A refrence Here

        //Here we need to increment Movie Views!
        m_GenreAVLtreesPtr[static_cast<int>(movie->getGenre())].RemoveElement(movie->getStatistics());
        movie->IncrementViews(1);
        m_GenreAVLtreesPtr[static_cast<int>(movie->getGenre())].InsertElement(movie, &(movie->getStatistics()));
        //
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    //Easy
    // TODO: Your code goes here
    return StatusType::SUCCESS;
    // TODO: Your code goes here
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
    if(movieId <= 0 || groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(!m_moviesbyId.ElementInTree(movieId)  || !m_groupsbyId.ElementInTree(groupId))
    {
        return StatusType::FAILURE;
    }
    try
    {
        std::shared_ptr<Movie> movie = m_moviesbyId.FindandGetSharedPtr(movieId);
        std::shared_ptr<Group> group = m_groupsbyId.FindandGetSharedPtr(groupId);
        if((!group->isVip() && movie->getVipOnly()) || (group->getSize() == 0))
        {
            return StatusType::FAILURE;
        }
        group->incrementGenreCount(movie->getGenre());



        //Increments the number of views of the to the group.
        m_GenreAVLtreesPtr[static_cast<int>(movie->getGenre())].RemoveElement(movie->getStatistics());
        movie->IncrementViews(group->getSize());
        m_GenreAVLtreesPtr[static_cast<int>(movie->getGenre())].InsertElement(movie, &(movie->getStatistics()));

        //GetId is suppost to return A refrence Here
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    //Easy
    // TODO: Your code goes here
    return StatusType::SUCCESS;
    // TODO: Your code goes here
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    int result;
    try
    {
        if(genre != Genre::NONE)
        {
            return m_GenreAVLtreesPtr[static_cast<int>(genre)].getSize();
        }
        return output_t<int>(m_moviesbyId.getSize());
        //Returns success
    }
    catch(const std::bad_alloc& e)
    {
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }

}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    try
    {
        if(output == NULL)
        {
            return StatusType::INVALID_INPUT;
        }
        if(genre != Genre::NONE)
        {
            int genreNum = static_cast<int>(genre);
            if(m_GenreAVLtreesPtr[genreNum].getSize() == 0)
            {
                return StatusType::FAILURE;
            }
            //int* keysDecending =

            Movie::Statistics* outputResult = m_GenreAVLtreesPtr[genreNum].GetKeysDescending();
            //I need to change it when i Get the chance!!!
            for (int i = 0; i < m_GenreAVLtreesPtr[genreNum].getSize(); i++)
            {
                output[i] = outputResult[i].getId();
            }
            delete[] outputResult;
            return StatusType::SUCCESS;

        }
        else
        {
            // Define a functor for comparing movie statistics
            CompareMovieStatisticsFunctor rightIsBiggerThanLeft;

// Defining an array of pointers to statistics for each genre
            Movie::Statistics* statsArrays[NUMBEROFGENRES];

// DErping an array to keep track of the current index within each genre's statistics array
            int currentIndices[NUMBEROFGENRES] = {0};

// Licking an array to store the size of each genre's statistics array
            int sizes[NUMBEROFGENRES];

// Procreating the arrays
            for (int genreIndex = 0; genreIndex < NUMBEROFGENRES; ++genreIndex) {
                statsArrays[genreIndex] = m_GenreAVLtreesPtr[genreIndex].GetKeysDescending();
                sizes[genreIndex] = m_GenreAVLtreesPtr[genreIndex].getSize();
            }

// Merge the arrays
            for (int outputIndex = 0; outputIndex < m_moviesbyId.getSize(); ++outputIndex) {
                int maxGenreIndex = -1;
                Movie::Statistics* maxStatistics = nullptr;
                // Find the maximum statistic among the current elements of all arrays
                for (int genreIndex = 0; genreIndex < NUMBEROFGENRES; ++genreIndex) {
                    if (currentIndices[genreIndex] < sizes[genreIndex]) { // if there are still elements left in this genre's statistics array
                        Movie::Statistics* currentStatistic = &(statsArrays[genreIndex][currentIndices[genreIndex]]);
                        if (maxStatistics == nullptr || rightIsBiggerThanLeft( *maxStatistics, *currentStatistic)) {
                            maxGenreIndex = genreIndex;
                            maxStatistics = currentStatistic;
                        }
                    }
                }
                // Update output with the maximum statistic's ID
                output[outputIndex] = maxStatistics->getId();
                // Increment the index of the array from which the maximum statistic was taken
                currentIndices[maxGenreIndex]++;
            }
            for (int i = 0; i < NUMBEROFGENRES; ++i) {
                delete[] statsArrays[i];
            }


        }










    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }

    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    // TODO: Your code goes here
    if(userId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(!m_usersbyId.ElementInTree(userId))
    {
        return StatusType::FAILURE;
    }
    try
    {
        std::shared_ptr<User> user = m_usersbyId.FindandGetSharedPtr(userId);
        if(genre != Genre::NONE) {
            return user->getNumGenreViews(genre);
        }
        else
        {
            int sum=0;
            for (int i = 0; i < NUMBEROFGENRES; ++i) {
                sum += user->getNumGenreViews(static_cast<Genre>(i));
            }
            return  sum;
        }
        //
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;

}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{

    if(userId <= 0 || movieId <=0 || rating<0 || rating > 100)
    {
        return StatusType::INVALID_INPUT;
    }
    if(!m_usersbyId.ElementInTree(userId) || !m_moviesbyId.ElementInTree(movieId))
    {
        return StatusType::FAILURE;
    }
    try
    {
        std::shared_ptr<User> user = m_usersbyId.FindandGetSharedPtr(userId);
        std::shared_ptr<Movie> movie = m_moviesbyId.FindandGetSharedPtr(movieId);
        if(!user->isVip() && movie->getVipOnly())
        {
            return StatusType::FAILURE;
        }
        m_GenreAVLtreesPtr[static_cast<int>(movie->getGenre())].RemoveElement(movie->getStatistics());

        movie->addRating(rating);



        m_GenreAVLtreesPtr[static_cast<int>(movie->getGenre())].InsertElement(movie, &(movie->getStatistics()));
        //
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
    if(groupId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if(!m_groupsbyId.ElementInTree(groupId) || m_groupsbyId.getSize() == 0)
    {
        return StatusType::FAILURE;
    }
    try
    {
        std::shared_ptr<Group> group = m_groupsbyId.FindandGetSharedPtr(groupId);

        //Used the SharePtr
        int maxGenre=0, MaxGenreNum=0;
        for (int i = 0; i < NUMBEROFGENRES; i++)
        {
            Genre genre = static_cast<Genre>(i);
            if(group->getGenreSumViewCount(genre) > maxGenre)
            {
                //Differince Between Sum Method and Noraml Watch method!

                maxGenre = group->getGenreViewCount(genre);
                MaxGenreNum = i;
            }
        }
        //No case Handled if this is an empty Tree
        //Review with instructors if this is ok
        if(m_GenreAVLtreesPtr[MaxGenreNum].getSize() == 0)
        {
            return  StatusType::FAILURE;
        }
        return (m_GenreAVLtreesPtr[MaxGenreNum].getMaxElement()).getId();
        //Important.. This tree is by ascending Id values!!!

        //
    }
    catch(const std::bad_alloc& e)
    {
        //It won't Catch Freeing Errors!
        return StatusType::ALLOCATION_ERROR;
    }
    //I should Aproprtiatly Catch the exception Of a void tree
    return StatusType::SUCCESS;
    //Finding  the best genre!



    // TODO: Your code goes here
}
