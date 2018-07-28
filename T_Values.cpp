#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

using namespace std; 
//Will most likely get away from using this namespace.  For now, using this namespace
//increases readability for your learning purposes.  

class T_subU {

public:

	vector<int> T_subU_Values;

	void printValues()
	{
		for (auto i = T_subU_Values.begin(); i != T_subU_Values.end(); i++)
		{
			cout << *i << " ";
		}
		cout << endl;
	}

};

//Purpose of this template is to create a set of unique values between two vectors.
//This 'Contained' template is adapted from:
//https://stackoverflow.com/questions/5529067/c-appending-one-vector-to-another-with-removal-of-duplicates

template <typename T> struct Contained
{
	const set<T> _set;
	template <typename It> Contained(const It& begin, const It& end) : _set(begin, end) {}
	bool operator()(const T& i) const
	{
		return _set.end() != _set.find(i);
	}
};

int generate_TsubUValue(int T_subU, int u_value)
{
	return T_subU - (2 * u_value);
}

int generate_lower_T_limit(int T_subU, int v2)
{
	return abs(T_subU - v2);
}

int generate_upper_T_limit(int T_subU, int v2)
{
	return abs(T_subU + v2);
}

bool valueAlreadyExist(vector<int> possibleValues, int T_value)
{
	return (find(possibleValues.begin(), possibleValues.end(), T_value) != possibleValues.end() );
}

void print_possible_values(vector<int> possibleValues)
{
	cout << "Possible values for T: ";
	for (auto i = possibleValues.begin(); i != possibleValues.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;
}

vector<int> generate_p_values(int v2)
{
	vector<int> p_values;

	for (int i = 0; i <= (2 * v2); i++)
	{
		p_values.push_back(i);
	}

	cout << "P values: ";

	for (auto i = p_values.begin(); i != p_values.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	return p_values;
}

vector<int> generate_q_values(int v1, int v2)
{
	vector<int> q_values;

	for (int i = 0; i <= (v1 - v2); i++)
	{
		q_values.push_back(i);
	}

	cout << "Q values: ";

	for (auto i = q_values.begin(); i != q_values.end(); i++)
	{
		cout << *i << " ";
	}
	cout << endl;

	return q_values;
}
 
int main()
{
	//Initiate beginning of program.
	cout << "Hello, Maddie" << endl;

	int v1, v2;

	//Get values of v1.
	cout << "Enter a value for v1: ";
	cin >> v1;

	//Get values of v2.
	cout << "Enter a value for v2: ";
	cin >> v2;

	cout << "v1 value is: " << v1 << endl;
	cout << "v2 value is: " << v2 << endl;

	//T_subU will always be the size of U, the given value of v1.

	//Create 2D array (array of arrays hence the double pointer).
	int** T_array = new int*[v1];

	for (int Tu = 0; Tu <= v1; Tu++)
	{
		T_array[Tu] = new int[v1];
	}

	//vector for possible values of T
	vector<int> possible_T_Values;

	//vector for T_subU objects
	vector<T_subU> T_subU_vector;
	T_subU_vector.resize(v1 + 1);

	//Populate 2D array.
	for (int Tu = 0; Tu <= v1; Tu++)
	{
		cout << "T" << Tu << ": ";
		for (int u = 0; u <= v1; u++)
		{
			//Generate T sub U value.
			T_array[Tu][u] = generate_TsubUValue(Tu, u);
			cout << T_array[Tu][u] << ", ";

			T_subU_vector[Tu].T_subU_Values.push_back(generate_TsubUValue(Tu, u));

			//If no possible values and no possible collisions, push value to vector.
			if (possible_T_Values.empty() 
				&& T_subU_vector[Tu].T_subU_Values[u] <= v1
				&& T_subU_vector[Tu].T_subU_Values[u] >= 0)
			{
				possible_T_Values.push_back( T_subU_vector[Tu].T_subU_Values[u] );
			}
			//Check for collisions of T values.  If does not already exist in vector, push value to vector.
			else if ( !valueAlreadyExist(possible_T_Values, T_subU_vector[Tu].T_subU_Values[u] ) && 
				      T_subU_vector[Tu].T_subU_Values[u] <= v1 && 
				      T_subU_vector[Tu].T_subU_Values[u] >= 0)
			{
				possible_T_Values.push_back( T_subU_vector[Tu].T_subU_Values[u] );
			}
		}
		cout << endl;

		//Check Tu = u, u-2, u-4 ...
		
		/*
		if ((Tu - 2) >= 0)
		{
			int i = 2;
			while( (Tu - i) >= 0)
			{
				//removing duplicates found in previous T vector.
				remove_copy_if( T_subU_vector[Tu - i].T_subU_Values.begin(), T_subU_vector[Tu - i].T_subU_Values.end(),
				                back_inserter(T_subU_vector[Tu].T_subU_Values), Contained<int>(T_subU_vector[Tu].T_subU_Values.begin(),
								T_subU_vector[Tu].T_subU_Values.end() ) );
				i = i + 2;
			}
			//cout << "Printing T" << Tu << ": ";
			//T_subU_vector[Tu].printValues();
		}*/
	}

	print_possible_values(possible_T_Values);
	cout << endl;

	for (int Tu = 0; Tu <= v1; Tu++)
	{		
		int count = 0; //For terminal formatting.

		cout << "For T" << Tu << ", T values are: ";

		//Generate limits of T.
		int lower_T = generate_lower_T_limit(Tu, v2);
		int upper_T;

		//T cannot be greater than v1; therefore, upper limit cannot exceed v1.
		if (generate_upper_T_limit(Tu, v2) > v1)
		{
			upper_T = v1;
		}
		else
		upper_T = generate_upper_T_limit(Tu, v2);

		//Check if values in range of limits exist as a possible value of T.
		for (lower_T; lower_T <= upper_T; lower_T++)
		{
			count++;
			if (valueAlreadyExist(possible_T_Values, lower_T))
			{
				if (count > 1) cout << ", ";
				cout << lower_T;			
			} 
		}
		cout << endl;
	}

	//Don't forget your p's and q's!!
	//Generate p and q values.
	vector<int> p_values = generate_p_values(v2);

	//if v1 is greater than v2, generate q values normally, else, produce q value of 0.
	vector<int> q_values = (v1 > v2) ? generate_q_values(v1, v2) : generate_q_values(0, 0) ;

	cout << endl;

	for (int i = 0; i <= v1; i++)
	{
		cout << "T" << i << ": ";
		T_subU_vector[i].printValues();
	}

	//Clean up memory

	vector<int>().swap(possible_T_Values);
	vector<int>().swap(p_values);
	vector<int>().swap(q_values);
	
	/* Why the fuck can I not free these values??? FREEDOM
	//Clean up memory of the array of arrays.
	for (int i = 0; i <= v1; i++)
	{
		delete[] T_array[i];
	}
	delete[] T_array;
	*/ //Commented out until I figure out how to free this memory from the tyranny of my pointers.

	return 0;	
}