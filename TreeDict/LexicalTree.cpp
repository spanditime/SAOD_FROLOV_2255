#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

using namespace std;

class LexicalTree
{
private:
    class Node
    {
    public:
        char c;
        unsigned int i;
        Node *next;
        Node *child;
        Node *parent;
        Node(char _c, Node *_parent)
        {
            parent = _parent;
            c = _c;
            i = 0;
            next = nullptr;
            child = nullptr;
        }
		~Node(){
			if(next != nullptr){
				delete next;
			}
			if(child != nullptr){
				delete child;
			}
		}
        void Add(string::iterator curr, string::iterator last, const unsigned int &count)
        {
            if (curr == last)
                i += count;
            else
            {
                char c = *(curr++);
                if (child == nullptr)
                {
                    child = new Node(c, this);
                    child->Add(curr, last, count);
                }
                else
                {
                    Node *it = child;
                    if (c < it->c)
                    {
                        Node *n = new Node(c, this);
                        n->next = it;
                        it->parent = n;
                        this->child = n;
                        child->Add(curr, last, count);
                    }
                    else
                        while (true)
                        {
                            if (it->c == c)
                            {
                                it->Add(curr, last, count);
                                return;
                            }
                            else if (it->next == nullptr)
                            {
                                it->next = new Node(c, it);
                            }
                            else if (it->c < c && it->next->c > c)
                            {
                                Node *n = new Node(c, it);
                                n->next = it->next;
                                it->next->parent = n;
                                it->next = n;
                            }
                            it = it->next;
                        }
                }
            }
        }
        unsigned int Count(string::iterator curr, string::iterator last)
        {
            if (curr == last)
                return i;
            else
            {
                char c = *(curr++);
                if (child == nullptr)
                {
                    return 0;
                }
                else
                {
                    Node *it = child;
                    while (true)
                    {
                        if (it->c == c)
                        {
                            return it->Count(curr, last);
                        }
                        if (it->next == nullptr)
                        {
                            return 0;
                        }
                        it = it->next;
                    }
                }
            }
        }
    };
    Node *root;

public:
    class const_iterator
    {
    private:
        friend class LexicalTree;
        Node *prev;
        Node *curr;
        string cstr;

        bool reverse_iterate_upwards()
        {
            while (curr != nullptr)
            {
                if (curr->parent == nullptr)
                {
                    step_upwards();
                    return false;
                }
                else if (curr->parent->child == curr)
                {
                    step_upwards();
                }
                else
                {
                    step_left();
                    return curr->child != nullptr;
                }
                if (curr->i != 0)
                {
                    return false;
                }
            }
            return false;
        }
        void reverse_iterate_downwards()
        {
            step_downwards();
            while (curr->next != nullptr || curr->child != nullptr)
            {
                if (curr->next != nullptr)
                {
                    reverse_iterate_right();
                }
                if (curr->child != nullptr)
                {
                    step_downwards();
                }
            }
        }
        void reverse_iterate_right()
        {
            while (curr->next != nullptr)
            {
                prev = curr;
                curr = curr->next;
            }
            cstr = cstr.substr(0, cstr.size() - 1) + curr->c;
        }
        void step_downwards()
        {
            prev = curr;
            curr = curr->child;
            cstr += curr->c;
        }
        void step_right()
        {
            prev = curr;
            curr = curr->next;
            if (cstr.size() <= 1)
            {
                cstr = string("") + curr->c;
            }
            else
            {
                cstr = cstr.substr(0, cstr.size() - 1) + curr->c;
            }
        }
        void step_left()
        {
            step_upwards();
            cstr += curr->c;
        }
        void step_upwards()
        {
            prev = curr;
            curr = curr->parent;
            if (cstr.size() <= 1)
            {
                cstr = "";
            }
            else
            {
                cstr = cstr.substr(0, cstr.size() - 1);
            }
        }
        bool iterate_upwards()
        {
            while (curr->next == nullptr)
            {
                if (curr->parent == nullptr)
                {
                    step_upwards();
                }
                else if (curr->parent->next == curr)
                {
                    // iterate left
                    while (curr->parent->child != curr)
                    {
                        prev = curr;
                        curr = curr->parent;
                    }
                    step_upwards();
                }
                else
                {
                    step_upwards();
                }
                if (curr == nullptr)
                {
                    return false;
                }
            }
            return true;
        }
        void iterate_downwards()
        {
            while (curr->i == 0)
            {
                step_downwards();
            }
        }

        const_iterator(Node *_curr)
        {
            curr = _curr;
            cstr = "";
            if (curr != nullptr)
            {
                iterate_downwards();
            }
        }
        const_iterator()
        {
            curr = nullptr;
            cstr = "";
        }

    public:
        // typedef typename A::difference_type difference_type;
        typedef pair<string, unsigned int> value_type;
        typedef const value_type &reference;
        typedef const value_type *pointer;
        typedef std::output_iterator_tag iterator_category; // or another tag

        const_iterator(const const_iterator &it)
        {
            curr = it.curr;
            cstr = it.cstr;
        }
        ~const_iterator(){

        };

        const_iterator &operator=(const const_iterator &it)
        {
            this->curr = it.curr;
            this->cstr = it.cstr;
            return *this;
        }
        bool operator==(const const_iterator &it) const
        {
            return curr == it.curr;
        }
        bool operator!=(const const_iterator &it) const
        {
            return curr != it.curr;
        }

        const_iterator &operator++()
        {
            if (curr->child != nullptr)
            {
                // take a step down
                step_downwards();
                // go down to a word
                iterate_downwards();
            }
            else if (curr->next != nullptr)
            {
                // take a step right
                step_right();

                // go down to a word
                iterate_downwards();
            }
            else
            {
                // go back up
                if (iterate_upwards())
                {
                    // if we havent got back to root
                    // go right
                    step_right();
                    iterate_downwards();
                }
            }
            return *this;
        };
        const_iterator &operator--()
        {
            if (reverse_iterate_upwards())
            {
                reverse_iterate_downwards();
            }
            return *this;
        }

        value_type operator*() const
        {
            return pair<string, int>(cstr, curr->i);
        }
        // pointer operator->() const;
    };
    class const_reverse_iterator : public const_iterator
    {
    private:
        friend class LexicalTree;
        const_reverse_iterator(Node *_curr) : const_iterator()
        {
            curr = _curr;
            cstr = "";
            if (curr != nullptr)
            {
                reverse_iterate_downwards();
            }
        }

    public:
        const_reverse_iterator &operator++()
        {
            const_iterator::operator--();
            return *this;
        }
        const_reverse_iterator &operator--()
        {
            const_iterator::operator++();
            return *this;
        }
    };

    LexicalTree()
    {
        root = new Node('\0', nullptr);
    }
	~LexicalTree()
	{
		cout<<"root deleted"<<endl;
		delete root;
	}
	void Add (string::iterator beg, string::iterator end, unsigned int count=1){
		root->Add(beg,end,count);
	}
    void Add(string str, unsigned int count = 1)
    {
        root->Add(str.begin(), str.end(), count);
    }
    unsigned int GetCount(string str)
    {
        return root->Count(str.begin(), str.end());
    }
    int Count()
    {
        unsigned int count = 0;
        for (const_iterator i = cbegin(); i != cend(); ++i)
        {
            count += (*i).second;
        }
        return count;
    }
    int SinglesCount()
    {
        unsigned int count = 0;
        for (const_iterator i = cbegin(); i != cend(); ++i)
        {
            count += ((*i).second != 0);
        }
        return count;
    }
    const_iterator cbegin()
    {
        if (root->child == nullptr)
        {
            return cend();
        }
        return const_iterator(root);
    }
    const_iterator cend()
    {
        return const_iterator(nullptr);
    }
    const_reverse_iterator crbegin()
    {
        if (root->child == nullptr)
        {
            return crend();
        }
        return const_reverse_iterator(root);
    }
    const_reverse_iterator crend()
    {
        return const_reverse_iterator(nullptr);
    }
    // returns vector of pairs, sorted in lexic order with word, count
    vector<pair<string, int>> LCR()
    {
        vector<pair<string, int>> ret;
        for (const_iterator i = cbegin(); i != cend(); ++i)
        {
            ret.push_back(*i);
        }
        return ret;
    }
};

// usage example
int main()
{
    string text;
	string searchword;
    LexicalTree tr;
	ifstream fin("engwiki_ascii.txt", ios::binary);
	if(!fin.is_open())
	{
		cout << "not open!" << endl;
		return 0;
	}
	text.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
	auto time_one = chrono::steady_clock::now();
	auto wb = text.begin();
	auto we = text.begin();
	while(we != text.end()){
		if(!( (*we >= 'a' && *we <= 'z') || (*we >= 'A' && *we <= 'Z') || *we == '\'')){
			if(we != wb){
				tr.Add(wb,we);
				// cout<<we-text.begin()<<"/"<<text.end()-text.begin()<<endl;
			}
			++we;
			wb = we;
		}else{
			++we;
		}

	}
	if(we != wb){
		tr.Add(wb,we);
	}
	
	auto count = tr.GetCount("wiki");
	auto time_two = chrono::steady_clock::now();
	
	cout<<"Count:"<<count<<"\nTime:"<< chrono::duration_cast<chrono::microseconds>(time_two - time_one).count()/1e6 << " sec\n";
}
