//Include necessary libraries
#include <wiringPi.h>
#include <stdio.h>

//Keep track of the GPIO pins that can be used for output
const int GPIO_PINS[] = [2, 3, 4, 7, 8, 14, 15, 17];

struct node
{
  stuct node *next;
  struct data *data;
};

struct data
{
  const int pin;
  //high = 1, low = 0; high = off, low = on
  int state;
};

//Add node at head
int addNode (struct node **head, int pin, int state)
{
  //new node
  struct node newNode = (struct node *) malloc(sizeof(struct node))

  if (newNode == NULL) return 0;

  newNode->(data.pin) = pin;
  newNode->(data.state) = state;

  newNode->next = *head;
  *head = newNode;

  return 1;
}

//Delete first node in list
int deleteFromList(struct node **head)
{
  //Return 1 if the list is empty
  if (head == NULL) return(1);

  //Keep handle to the node to be deleted (head)
  struct node *p = NULL;
  p = *head;

  //Set head to node after p (after head)
  *head = p->next;

  //Free the memory!
  free(p);
  p = NULL;

  return(0);

}

//Delete list of nodes after we don't need it anymore
void deleteList(struct node **head)
{
	for (int i=0; i<8; i++)
  {
    deleteFromList(head);
  }
}

//Turn LED on or off depending on it's state
void change_led(struct node *myNode)
{
  //Turn LED on
  if (myNode->state == 0)
  {
    digitalWrite(myNode->(data.pin), LOW);
  }

  else
  {
    digitalWrite(myNode->(data.pin), HIGH);
  }
}

int main(void)
{
  if(wiringPiSetup() == -1){
    printf("Error on wiringPi setup\n");
    return 1;
  }

  struct node **head;

  //Initialize linked list; each node will correspond to digital output from peripheral to PI
  for (int i=0; i<7; i++)
  {
    addNode(head, GPIO_PINS[i], 1);
  }

  struct node *p = *head;

  //Set all the pins in linked list to output
  for(int i=0; int i<8; i++)
  {
    while (p != NULL)
    {
      pinMode(p->(data.pin), OUTPUT)
      p = p->next;
    }
  }

  //Have the lights turn on and off sequentially down the bar graph using the linked list
  //Do this 10 times

  p = *head;

  for(int i=0; i<10; i++)
  {
    for (int i=0; i<8; i++)
    {
      while (p != NULL)
      {
        p->(data.pin) = 0;
        change_led(p);
        delay(100);
        p->(data.pin) = 1;
        change_led(p);
        p = p->next;
      }
    }
  }

  //Delete the list to free up memory
  deleteList(head);

  return 0;
}
