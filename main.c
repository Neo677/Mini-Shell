int g_shell_pid;

int main(void)
{
    g_shell_pid = getpid();  // Allowed since it's called once at startup
    // ... rest of main function ...
} 