#include "StreamingDBa1.h"

streaming_database::streaming_database()
{
	//Let's make the AVL Tree's need and change them ad hoc 
	// TODO: Your code goes here

	//Creating Trees of Movies Ranked By Genre!
	CompareMovieStatisticsFunctor StatsticsMoviecomapreFunctor;
	
	//making an array of AVL TREES!
	AVLTREE<Movie, CompareMovieStatisticsFunctor, int>* movieTreesArray = new AVLTREE<Movie, CompareMovieStatisticsFunctor, int>[NUMBEROFGENRES];

	m_GenreAVLtreesPtr = new AVLTREE<Movie, CompareMovieStatisticsFunctor, Movie::Statistics>[NUMBEROFGENRES];
	//More Avl Trees By statistics
}

streaming_database::~streaming_database()
{
	for (int i = 0; i < NUMBEROFGENRES; i++)
	{
		m_GenreAVLtreesPtr[i].~AVLTREE();
		//Calling the Destructors
	}
	delete m_GenreAVLtreesPtr;

	
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
		Movie remMovie  = m_moviesbyId.Find(movieId);
		m_GenreAVLtreesPtr[static_cast<int>(remMovie.getGenre())].RemoveElement(remMovie.getStatistics());
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
		User remUser = m_usersbyId.Find(userId);
		
		if(remUser.inGroup())
		{
			(remUser.getGroupPtr())->deleteUser(userId);
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
	//Easy
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
	//Just Remove it from the tree!
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
