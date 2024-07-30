void prints(char *string)
{
    int idx = 0;
    char c;
    char *memaddr = (char *)0xb8000;
    while (c = *string++)
    {
        memaddr[idx++] = c;
        memaddr[idx++] = 0x8E;
    }
}

void main()
{
    char *memaddr = (char *)0xb8000;
    memaddr[1] = 0x8F;
    memaddr[0] = 'X';

    prints("Hello there from the other side.. the other side..");
}