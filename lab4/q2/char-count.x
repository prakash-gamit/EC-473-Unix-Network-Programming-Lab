struct string_in{
    string in_string<1024>;
    char in_char;
};


struct count_out{
    long count;
};


program CHARACTERCOUNT_PROG {
    version CHARACTERCOUNT_VERS {
    count_out getCharacterCount(string_in) = 1;
    } = 1;
} = 0x31203923;
