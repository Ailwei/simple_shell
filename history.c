#include "shell.h"

/**
 * get_history_filename - Get the history file name
 * @info: Pointer to ShellInfo structure
 *
 * Return: Allocated string containing the history file name
 */
char *get_history_filename(ShellInfo *info)
{
    char *home_dir;

    home_dir = _getenv(info, "HOME=");
    if (!home_dir)
        return (NULL);

    char *filename = malloc(sizeof(char) * (_strlen(home_dir) + _strlen(HISTORY_FILE) + 2));
    if (!filename)
        return (NULL);

    filename[0] = 0;
    _strcpy(filename, home_dir);
    _strcat(filename, "/");
    _strcat(filename, HISTORY_FILE);

    return (filename);
}

/**
 * write_history_to_file - Write the history to a file
 * @info: Pointer to ShellInfo structure
 *
 * Return: 1 on success, else -1
 */
int write_history_to_file(ShellInfo *info)
{
    ssize_t fd;
    char *filename = get_history_filename(info);
    ShellHistoryEntry *entry;

    if (!filename)
        return (-1);

    fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(filename);

    if (fd == -1)
        return (-1);

    for (entry = info->history; entry; entry = entry->next)
    {
        _putsfd(entry->command, fd);
        _putcharfd('\n', fd);
    }

    _putcharfd(BUF_FLUSH, fd);
    close(fd);
    return (1);
}

/**
 * read_history_from_file - Read the history from a file
 * @info: Pointer to ShellInfo structure
 *
 * Return: Number of history entries read, or 0 on failure
 */
int read_history_from_file(ShellInfo *info)
{
    int i, last = 0, linecount = 0;
    ssize_t fd, rdlen, file_size = 0;
    struct stat st;
    char *buf = NULL, *filename = get_history_filename(info);

    if (!filename)
        return (0);

    fd = open(filename, O_RDONLY);
    free(filename);

    if (fd == -1)
        return (0);

    if (!fstat(fd, &st))
        file_size = st.st_size;

    if (file_size < 2)
        return (0);

    buf = malloc(sizeof(char) * (file_size + 1));
    if (!buf)
        return (0);

    rdlen = read(fd, buf, file_size);
    buf[file_size] = 0;

    if (rdlen <= 0)
        return (free(buf), 0);

    close(fd);

    for (i = 0; i < file_size; i++)
    {
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            add_history_entry(info, buf + last, linecount++);
            last = i + 1;
        }
    }

    if (last != i)
        add_history_entry(info, buf + last, linecount++);

    free(buf);
    info->histcount = linecount;

    while (info->histcount-- >= MAX_HISTORY_ENTRIES)
        delete_history_entry(&(info->history), 0);

    renumber_history_entries(info);
    return (info->histcount);
}

/**
 * add_history_entry - Add a new entry to the command history
 * @info: Pointer to ShellInfo structure
 * @entry: The command entry to add
 *
 * Return: 1 on success, else 0
 */
int add_history_entry(ShellInfo *info, char *entry, int linecount)
{
    ShellHistoryEntry *new_entry = malloc(sizeof(ShellHistoryEntry));
    if (!new_entry)
        return (0);

    new_entry->linecount = linecount;
    new_entry->command = _strdup(entry);
    new_entry->next = NULL;

    if (!new_entry->command)
    {
        free(new_entry);
        return (0);
    }

    if (!info->history)
    {
        info->history = new_entry;
    }
    else
    {
        ShellHistoryEntry *last = info->history;
        while (last->next)
            last = last->next;
        last->next = new_entry;
    }

    return (1);
}

/**
 * renumber_history_entries - Renumber the history entries
 * @info: Pointer to ShellInfo structure
 *
 * Return: The new histcount
 */
int renumber_history_entries(ShellInfo *info)
{
    int linecount = 0;
    ShellHistoryEntry *entry = info->history;

    while (entry)
    {
        entry->linecount = linecount++;
        entry = entry->next;
    }

    return (info->histcount = linecount);
}

