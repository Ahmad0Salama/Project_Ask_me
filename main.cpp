// وَأَن لَّيْسَ لِلْإِنسَانِ إِلَّا مَا سَعَىٰ ( 39 ) وَأَنَّ سَعْيَهُ سَوْفَ يُرَىٰ ( 40 ) ثُمَّ يُجْزَاهُ الْجَزَاءَ الْأَوْفَىٰ ( 41 )
#include <bits/stdc++.h>
using namespace std ;

    class user ;
    class questions ;
    int read_int() ;
    int read_int( int min_ , int max_ ) ;
    void main_menu() ;

user * curr_user_ptr = nullptr ;

// read functions

string read_string()
{
    string temp ;
    cin.clear() ;
    cin.ignore( numeric_limits<streamsize>::max() , '\n' ) ;
    
    while ( true )
    {
        getline( cin , temp ) ;
        if ( !temp.empty() ) return temp ;

        cout << "Not valid string value\n" ;
    }
    return temp ;
}

int read_int()
{
    int temp ;
    while ( true )
    {
        if ( cin >> temp )
        {
            cin.ignore( numeric_limits<streamsize>::max() , '\n' ) ; // Clear the input buffer
            return temp ;
        }

        cout << "Not integer value\n" ;
        cin.clear() ;
        cin.ignore( numeric_limits<streamsize>::max() , '\n' ) ;
    }
}

string read_string( const string& prompt )
{
    cout << prompt ;
    return read_string() ;
}

int read_int( int min_ , int max_ )
{
    int temp = read_int() ;

    while ( !( min_ <= temp && temp <= max_ ) )
    {
        cout << "The number must be in range {" << min_ << "  , " << max_ << "}\n" ;
        temp = read_int() ;
    }
    
    return temp ;
}

int read_int( const string& prompt )
{
    cout << prompt ;
    return read_int() ;
}

int read_int( const string& prompt , int min_ , int max_ )
{
    cout << prompt ;
    return read_int( min_ , max_ ) ;
}

int print_menu( const vector<string>& menu )
{
    cout << "Menu:\n" ;
    int n = menu.size() ;
    for ( int i = 0 ; i < n ; i++ ) cout << "\t" << i + 1 << ": " << menu[i] << "\n" ;
    return read_int( 1 , n ) ;
}

class user
{
    private:
        int id ;
        string name , pass ;

        set < questions * > curr_questions ;      // Questions asked by this user
        set < questions * > curr_answers ;        // Questions answered by this user
        set < questions * > curr_none_answered ;  // Questions to this user not yet answered

        static int id_cnt ;

    public:
        static map < int , user * > curr_users ;

        user( const string& name , const string& pass )
        {
            id = ++id_cnt ;
            this->name = name ;
            this->pass = pass ;
        }

        user() : user( read_string( "Enter name: " ) , read_string( "Enter password: " ) ) {}

        int get_id() const { return id ; }
        string get_name() const { return name ; }

        static int read_id()
        {
            int id ;
            while ( true )
            {
                cout << "\nEnter your id ( to back enter -1 ): " ;
                cin >> id ;
                cin.ignore( numeric_limits<streamsize>::max() , '\n' ) ; // Clear input buffer

                if ( id == -1 ) return -1 ;
                if ( curr_users.find( id ) != curr_users.end() )
                    return id ;

                cout << "\nNo user with this id , try again!" ;
            }
        }

        static user* sign_in()
        {
            int id = read_id() ;
            if ( id == -1 ) return nullptr ;

            user* curr = curr_users[id] ;
            string pass ;

            while ( true )
            {
                cout << "\nEnter your password ( to back enter -1 ): " ;
                cin >> pass ;
                cin.ignore( numeric_limits<streamsize>::max() , '\n' ) ; // Clear input buffer

                if ( pass == "-1" ) return nullptr ;
                if ( curr->pass == pass ) break ;

                cout << "\nInvalid password , try again!" ;
            }

            return curr ;
        }

        void sign_out()
        {
            curr_user_ptr = nullptr ;
        }

        static string print_name( int id )
        {
            if ( curr_users.find( id ) == curr_users.end() ) return "Unknown" ;
            return curr_users[id]->get_name() ;
        }

        void change_pass()
        {
            string pass = read_string( "\nEnter your new password ( to back enter \"-1\" ): " ) ;
            
            if ( pass == "-1" ) return ;
            this->pass = pass ;

            cout << "\nPassword was changed!\n" ;
        }

        void change_name()
        {
            string name = read_string( "\nEnter your new name ( to back enter \"-1\" ): " ) ;
            
            if ( name == "-1" ) return ;
            this->name = name ;

            cout << "\nName was changed!\n" ;
        }

        void add_question( questions* temp )
        {
            if ( temp ) curr_questions.insert( temp ) ;
        }

        void add_answer( questions* temp )
        {
            if ( temp ) {
                curr_none_answered.erase( temp ) ;
                curr_answers.insert( temp ) ;
            }
        }

        void add_none_answered( questions* temp )
        {
            if ( temp ) curr_none_answered.insert( temp ) ;
        }

        void remove_question( questions* temp )
        {
            if ( temp ) {
                curr_questions.erase( temp ) ;
                curr_answers.erase( temp ) ;
                curr_none_answered.erase( temp ) ;
            }
        }

        void answer_question() ;

        static void print_all_user()
        {
            if ( curr_users.empty() ) {
                cout << "No users in the system.\n" ;
                return ;
            }
            cout << "System Users:\n" ;
            for ( const auto& [id , ptr] : curr_users ) {
                cout << "ID: " << id << " , Name: " << ptr->get_name() << "\n" ;
            }
        }

        void print_to_me() ;
        void print_to_from() ;
        
        ~user() ;
} ;

    int user::id_cnt = 0 ;
    map < int , user * > user::curr_users ;

class questions
{
        int id ;
        int owner_id , to_user_id ;
        string question , answer ;
        bool is_valid ;

        static int id_cnt ;

    public:

        static map < int , questions * > curr_questions ;

        questions()
        {
            this->id = ++ id_cnt ;
            is_valid = false ;
            
            // Check if current user exists
            if ( !curr_user_ptr )
            {
                cout << "Error: No user logged in!\n" ;
                id_cnt -- ;
                return ;
            }
            
            this->owner_id = curr_user_ptr->get_id() ;

            cout << "To which user do you want to ask? " ;
            this->to_user_id = user::read_id() ;
            
            if ( to_user_id == -1 ) 
            {
                id_cnt -- ;
                return ;
            }

            this->question = read_string( "Enter your question: " ) ;
            
            // Add to user's question lists
            if ( user::curr_users.find( owner_id ) != user::curr_users.end() )
                user::curr_users[owner_id]->add_question( this ) ;

            if ( user::curr_users.find( to_user_id ) != user::curr_users.end() )
                user::curr_users[to_user_id]->add_none_answered( this ) ;

            curr_questions[id] = this ;
            is_valid = true ;
            cout << "Question created successfully with ID: " << id << "\n" ;
        }

        bool is_question_valid() const { return is_valid ; }

        static int read_id()
        {
            int id ;
            while ( true )
            {
                cout << "\nEnter Question id ( to back enter -1 ): " ;
                cin >> id ;
                cin.ignore( numeric_limits<streamsize>::max() , '\n' ) ; // Clear input buffer

                if ( id == -1 ) return -1 ;
                if ( curr_questions.find( id ) != curr_questions.end() )
                    return id ;

                cout << "No Question with this id , try again!\n" ;
            }
        }

        int get_id() const { return id ; }
        int get_owner_id() const { return owner_id ; }
        int get_to_user_id() const { return to_user_id ; }

        void reset_answer()
        {
            if ( !curr_user_ptr || curr_user_ptr->get_id() != to_user_id )
            {
                cout << "Invalid operation you don't have the access\n" ;
                return ;
            }

            if ( user::curr_users.find( to_user_id ) != user::curr_users.end() )
                user::curr_users[to_user_id]->add_none_answered( this ) ;

            this->answer.clear() ;
        }
        
        void set_answer()
        {
            if ( !curr_user_ptr || curr_user_ptr->get_id() != to_user_id )
            {
                cout << "Invalid operation you don't have the access\n" ;
                return ;
            }

            if ( user::curr_users.find( to_user_id ) != user::curr_users.end() )
                user::curr_users[to_user_id]->add_answer( this ) ;
            
            this->answer = read_string( "Enter your answer: " ) ;
            cout << "Answer added successfully!\n" ;
        }

        void set_question()
        {
            if ( !curr_user_ptr || curr_user_ptr->get_id() != owner_id )
            {
                cout << "Invalid operation you don't have the access\n" ;
                return ;
            }

            this->question = read_string( "Enter new question: " ) ;
        }

        void print_question()
        {
            cout << "\tQuestion with id: " << id << " , from \"" << user::print_name( owner_id ) << "\" to \"" << user::print_name( to_user_id ) << "\"\n" ;
            cout << "\t\t\t Q: " << question << "\n" ;

            if ( !answer.empty() ) cout << "\t\t\t A: " << answer << "\n" ;
            else cout << "\t\t\t A: [Not answered yet]\n" ;
        }
        
        static void print_all_question()
        {
            if ( curr_questions.empty() )
            {
                cout << "No questions in the system.\n" ;
                return ;
            }
            
            cout << "All Questions in the system:\n" ;
            for ( const auto& [id , ptr] : curr_questions )
                ptr->print_question() ;
        }

        static void delete_question ( int question_id )
        {
            auto it = curr_questions.find( question_id ) ;
            
            if ( it == curr_questions.end() ) 
            {
                cout << "Question not found!\n" ;
                return ;
            }

            questions* q = it->second ;
            
            if ( !curr_user_ptr || curr_user_ptr->get_id() != q->owner_id )
            {
                cout << "Invalid operation , you don't have access\n" ;
                return ;
            }

            // Remove from users' sets
            if ( user::curr_users.find( q->owner_id ) != user::curr_users.end() )
                user::curr_users[q->owner_id]->remove_question( q ) ;

            if ( user::curr_users.find( q->to_user_id ) != user::curr_users.end() )
                user::curr_users[q->to_user_id]->remove_question( q ) ;


            curr_questions.erase( question_id ) ;
            
            delete q ;
            cout << "Question deleted successfully!\n" ;
        }
} ;

    int questions::id_cnt = 0 ;
    map < int , questions * > questions::curr_questions ;

void user::answer_question() 
{
    if ( curr_none_answered.empty() )
    {
        cout << "No unanswered questions for you.\n" ;
        return ;
    }
    
    cout << "Your unanswered questions:\n" ;
    for ( auto q : curr_none_answered ) {
        if ( q ) q->print_question() ;
    }
    
    int id = questions::read_id() ;
    if ( id == -1 ) return ;
    
    auto it = questions::curr_questions.find( id ) ;
    if ( it != questions::curr_questions.end() && it->second ) {
        // Check if this question is actually in the user's unanswered list
        if ( curr_none_answered.find( it->second ) != curr_none_answered.end() )
            it->second->set_answer() ;
        else
            cout << "This question is not in your unanswered list!\n" ;

    }
}

void user::print_to_me()
{
    if ( curr_none_answered.empty() && curr_answers.empty() )
    {
        cout << "No questions directed to you.\n" ;
        return ;
    }
    
    cout << "Questions to you:\n" ;
    
    if ( !curr_none_answered.empty() )
    {
        cout << "Unanswered:\n" ;
        for ( auto it : curr_none_answered )
            if ( it ) it->print_question() ;
    }
    
    if ( !curr_answers.empty() )
    {
        cout << "Answered:\n" ;
        for ( auto it : curr_answers )
            if ( it ) it->print_question() ;
    }
}

void user::print_to_from()
{
    if ( curr_questions.empty() )
    {
        cout << "You haven't asked any questions.\n" ;
        return ;
    }
    
    cout << "Questions from you:\n" ; 
    for ( auto it : curr_questions )
        if ( it ) it->print_question() ;
}

user::~user()
{
    // Remove user from global map
    curr_users.erase( id ) ;

    // Clean up questions
    vector < questions * > to_delete ;
    
    for ( auto q : curr_questions ) if ( q ) to_delete.push_back( q ) ;
    for ( auto q : curr_answers ) if ( q ) to_delete.push_back( q ) ;
    for ( auto q : curr_none_answered ) if ( q ) to_delete.push_back( q ) ;
    
    // Remove duplicates
    sort ( to_delete.begin() , to_delete.end() ) ;
    to_delete.erase( unique( to_delete.begin() , to_delete.end() ) , to_delete.end() ) ;
    
    for ( auto q : to_delete ) 
    {
        questions::curr_questions.erase( q->get_id() ) ;
        delete q ;
    }
    
    curr_questions.clear() ;
    curr_answers.clear() ;
    curr_none_answered.clear() ;
}

void sign_menu()
{
    vector<string> menu = 
    { 
        "Login" ,
        "Sign Up" ,
        "Exit"
    } ;

    int type = print_menu( menu ) ;

    if ( type == 1 )
    {
        curr_user_ptr = user::sign_in() ;
        if ( curr_user_ptr )
        {
            cout << "\nWelcome , " << curr_user_ptr->get_name() << "!\n" ;
            main_menu() ;
        }
        else
        {
            cout << "\nLogin failed or cancelled.\n" ;
            sign_menu() ;
        }
    }
    else if ( type == 2 )
    {
        user* new_user = new user() ;
        user::curr_users[new_user->get_id()] = new_user ;
        cout << "User created with ID = " << new_user->get_id() << "\n" ;
        cout << "Please login with your new account.\n" ;
        sign_menu() ;
    }
    else
    {
        cout << "Goodbye!\n" ;
        return ;
    }
}

void main_menu()
{
    if ( !curr_user_ptr )
    {
        cout << "Error: No user logged in!\n" ;
        sign_menu() ;
        return ;
    }

    vector <string> menu = 
    {
        "Print Questions To Me" ,
        "Print Questions From Me" , 
        "Answer Question" ,
        "Delete Question" ,
        "Ask Question" ,
        "List System Users" ,
        "Feed" ,
        "Logout"
    } ;

    int type = print_menu( menu ) ;

    if ( type == 1 ) curr_user_ptr->print_to_me() ;
    else if ( type == 2 ) curr_user_ptr->print_to_from() ;
    else if ( type == 3 ) curr_user_ptr->answer_question() ;
    else if ( type == 4 ) 
    {
        int id = questions::read_id() ;
        if ( id != -1 )
            questions::delete_question( id ) ;
    }
    else if ( type == 5 ) {
        questions* new_q = new questions() ;
        if ( !new_q->is_question_valid() ) {
            delete new_q ;
        }
    }
    else if ( type == 6 ) user::print_all_user() ;
    else if ( type == 7 ) questions::print_all_question() ;
    else if ( type == 8 ) 
    {
        curr_user_ptr->sign_out() ;
        cout << "Logged out successfully!\n" ;
        sign_menu() ;
        return ;
    }

    main_menu() ;
}

int main()
{

    cout << "Welcome to the Q&A System!\n" ;
    cout << "============================\n" ;
    sign_menu() ;


    return 0 ;
}