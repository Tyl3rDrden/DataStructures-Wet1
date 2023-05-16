#include "StreamingDBa1.h"

streaming_database::streaming_database()
{
	//Let's make the AVL Tree's need and change them ad hoc 
	CompareGroupIDFunctor IdMoviecompareFunctor;
	AVLTREE<Movie, CompareGroupIDFunctor>  m_moviesbyId(IdMoviecompareFunctor);

	CompareGroupIDFunctor IdGroupcompareFunctor;
	AVLTREE<Group, CompareGroupIDFunctor>  m_groupbyId(IdGroupcompareFunctor);

	CompareUserIDFunctor IdUsercompareFunctor;
	AVLTREE<User, CompareUserIDFunctor>  m_userbyId(IdUsercompareFunctor);
	// TODO: Your code goes here

	//More Avl Trees By statistics
}

streaming_database::~streaming_database()
{
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
		std::shared_ptr<Movie> newMoviePtr = std::make_shared<Movie>(movieId, genre, views, vipOnly);
		if(!m_moviesbyId.Find(*newMoviePtr))
		{//Returns NullPtr if cannot find the movie By id !
			m_moviesbyId.InsertElement(newMoviePtr);

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
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}


