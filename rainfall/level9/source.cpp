#include <string.h>
#include <unistd.h>

class N {

    public:
        char annotation[100]; /* offset 4 */
        int value; /* offset 0x68 */

    public:
        N(int number)
        {
            this->value = number;
        }
        
        /* create a v-table */
        virtual N operator+(N &other)
        {
            return (N(this->value + other.value));
        }

        N operator-(N &other)
        {
            return (N(this->value - other.value));
        }

        void setAnnotation(char *string)
        {
            memcpy(this->annotation, string, strlen(string));
        }
};

typedef N (*func_t)(N*, N*);

int main(int argc, char *const argv[])
{
    if (argc < 2)
        _exit(1);
    
    N *a = new N(5);
    N *b = new N(6);

    a->setAnnotation(argv[1]);

    // void** vtable_ptr = reinterpret_cast<void**>(b); /* &((void**)b)[0] */
    // void* vtable = *vtable_ptr;
    // func_t* func = reinterpret_cast<func_t*>(vtable); /* &vtable[0] */
    // return ((*func)(a, b).value);

    return (b->operator+(*a).value);
}
