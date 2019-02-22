struct node {
	node* next;
	string data;
};

class LinkedList
{
public:

	node* head;
	node* tail;
	/*DEFAULT CONSTRUCTOR*/
	LinkedList() 
	{
		head = NULL;
		tail = NULL;
	}

	void push(char* data) 
	{
		string str(data);
		
		/*LIST IS EMPTY*/
		if(head == NULL)
		{
			head = new node();
			head->data = data;
			head->next = NULL;
			tail = head;
		}
		/*ONE ELEMENT IN LIST*/
		else if(head == tail)
		{
			tail = new node();
			tail->data = data;
			tail->next = NULL;
			head->next = tail;
		}
		/*OTHER CASES*/
		else
		{
			node* temp = new node();
			temp->data = data;
			temp->next = NULL;
			tail->next = temp;
			tail = temp;
		}
	}

	void remove(char* data)
	{
		int flag=0;
		node* iter = head;
		string str(data);
	
		if(data == iter->data)
		{
			head = iter->next;
			flag=1;
		}
	
		while(iter->next !=NULL && flag!=1)
		{
			if(iter->next->data == data)
			{
				if(iter->next == tail)
				{
					tail=iter;
				}
				
				iter->next = iter->next->next;
				break;
			}
			iter = iter->next;
		}
	}
	/*IF LIST IS EMPTY*/
	bool empty()
	{
		if(head== NULL)
			return true;
	
		else 
			return false;
	}
	/*FUNCTION FOR POP*/
	void pop()
	{
		char *d = &(tail->data)[0];
		remove(d);	
	}
	/*FUNCTION WHICH RETURNS TOP ELEMENT*/
	char* top()
	{
		char *d = &(tail->data)[0];
		return d;
	}
	/*PRINTING LIST*/
	void printList()
	{
		node* iter = head;
		while(iter!=NULL)
		{
			//if(iter->next!=NULL)
			if(iter!=head)
				cout<<":";
			cout<<iter->data;
			iter=iter->next;
		}
	}
	/*FUNCTION RETURNS NUMBER OF ELEMENTS IN THE LIST*/
	int size()
	{
		int len=0;
		node* iter = head;
		while(iter!=NULL)
		{
			iter=iter->next;
			len++;
		}
	return len;
	}
	/*FUNCTION RETURNING INDEX OF PATH IN THE LIST*/
	char* get(int index)
	{	
		node* iter = head;
		int i=0;
		while(i < index)
		{
			iter=iter->next;
			i++;
		}
		char *d = &(iter->data)[0];

	return d;		
	}
};
