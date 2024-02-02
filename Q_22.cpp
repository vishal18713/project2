#include <iostream>
using namespace std;

class Node
{
public:
    int power;
    int coefficient;
    Node *next;

    Node(int power, int coefficient)
    {
        this->power = power;
        this->coefficient = coefficient;
        this->next = NULL;
    }
};

void printPolynomial(Node *head)
{
    while (head != NULL)
    {
        cout << head->coefficient << "x^" << head->power << " ";
        if (head->next != NULL)
            cout << "+ ";
        head = head->next;
    }
    cout << endl;
}

Node *createPolynomial()
{
    Node *head = NULL;
    Node *current = NULL;

    int power, coefficient;
    char addMore;

    do
    {
        cout << "Enter the degree of the term: ";
        cin >> power;
        cout << "Enter the coefficient of x^" << power << ": ";
        cin >> coefficient;

        Node *newNode = new Node(power, coefficient);

        if (head == NULL)
        {
            head = newNode;
            current = head;
        }
        else
        {
            current->next = newNode;
            current = newNode;
        }

        cout << "Do you want to add more terms? (y/n): ";
        cin >> addMore;
    } while (addMore == 'y' || addMore == 'Y');

    return head;
}

Node *multiplyPolynomials(Node *poly1, Node *poly2)
{
    Node *result = NULL;

    while (poly1 != NULL)
    {
        Node *temp = poly2;
        while (temp != NULL)
        {
            int newPower = poly1->power + temp->power;
            int newCoefficient = poly1->coefficient * temp->coefficient;

           
            Node *existingTerm = result;
            while (existingTerm != NULL)
            {
                if (existingTerm->power == newPower)
                {
                    existingTerm->coefficient += newCoefficient;
                    break;
                }
                existingTerm = existingTerm->next;
            }

            if (existingTerm == NULL)
            {
                Node *newNode = new Node(newPower, newCoefficient);
                newNode->next = result;
                result = newNode;
            }

            temp = temp->next;
        }

        poly1 = poly1->next;
    }

    return result;
}

int main()
{
    cout << "Enter coefficients for Polynomial 1 (sorted by power in descending order): \n";
    Node *poly1 = createPolynomial();

    cout << "Enter coefficients for Polynomial 2 (sorted by power in descending order):\n";
    Node *poly2 = createPolynomial();

    Node *result = multiplyPolynomials(poly1, poly2);
    cout << "Input Polynomial 1: ";
    printPolynomial(poly1);

    cout << "Input Polynomial 2: ";
    printPolynomial(poly2);

    cout << "Output Polynomial Multiplication: ";
    printPolynomial(result);

   
    while (poly1 != NULL)
    {
        Node *temp = poly1;
        poly1 = poly1->next;
        delete temp;
    }

    while (poly2 != NULL)
    {
        Node *temp = poly2;
        poly2 = poly2->next;
        delete temp;
    }

    while (result != NULL)
    {
        Node *temp = result;
        result = result->next;
        delete temp;
    }

    return 0;
}
