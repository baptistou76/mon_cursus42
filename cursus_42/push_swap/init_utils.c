int stack_len(t_stack_node *stack)
{
    int count = 0;
    if(!stack)
        return(0);
    while(stack)
    {
        stack = stack->next;
        count++;
    }
    return(count);
}
t_stack_node *find_last(t_stack_node *stack)
{
    if(!stack)
        return(NULL);
    while(stack->next)
        stack->next;
    return(stack);
}
t_stack_node *find_min(t_stack_node *stack)
{
    long min;
    t_stack_node *min_node;
    if(!stack)
        return(NULL);
    while(stack)
    {
        if(stack->nbr < min)
        {
            min = stack->nbr;
            min_node = stack;
        }
        stack = stack->next;
    }
    return(min_node);
}
t_stack_node *find_max(t_stack_node *stack)
{
    long max;
    t_stack_node *max_node;
    if(!stack)
        return(NULL);
    max = LONG_MIN;
    while(stack)
    {
        if(stack->nbr > max)
        {
            max = stack->nbr;
            max_node = stack;
        }
        stack = stack->next;
    }

    return(max_node);
}
bool stack_sorted(t_stack_node *stack)
{
    if(!stack)
        return(1);
    while(stack->next)
    {
        if(stack->nbr > stack->next->nbr)
            return(false);
        stack = stack->next;
    }
    return(true);
}
t_stack_node *get_cheapest(t_stack_node *stack)
{
    if(!stack)
        return(NULL);
    while(stack)
    {
        if(stack->cheapest)
            return(stack);
        stack = stack->next;
    }
    return(NULL);
}
void prep_for_push(t_stack_node **stack, t_stack_node *top_node, char stack_name)
{
    while(*stack != top_node)
    {
        if(stack_name == 'a')
        {
            if(top_node->above_median)
                ra(stack, false);
            else
                rra(stack, false);
        }
        else if(stack_name == 'b')
        {
            if(top_node->above_median)
                rb(stack,false);
            else 
                rrb(stack, false);
        }
    }
}
int error_syntax(char *str_n)
{
    if(!(*str_n == '+') || *str_n == '-' || (*str_n >= '0' && *str_n <= '9'))
        return(1);
    if((*str_n == '+' || *str_n == '-') && !(str_n[1] >= '0' && str_n[1] <= '9'))
        return(1);
    while(++str_n)
    {
        if(!(*str_n >= '0' && *str_n <= '9'))
            return(1);
    }
    return(0);
}
int error_duplicate(t_stack_node *a, int n)
{
    if(!a)
        return(0);
    while(a)
    {
        if(a->nbr == n)
            return(1);
        a = a->next;
    }
    return(0);
}
void free_stack(t_stack_node **stack)
{
    t_stack_node *tmp;
    t_stack_node *current;
    if(!stack)
        return;
    current = *stack;
    while(current)
    {
        tmp = current->next;
        current->nbr = 0;
        free(current);
        current  = tmp;
    }
    *stack = NULL;
}

void free_error(t_stack_node **a)
{
    free_stack(a);
    ft_printf("Error\n");
    exit(1);
}
static void swap(t_stack_node **head)
{
    if(!*head || !(*head)->next)
        return;
    *head = (*head)->next;
    (*head)->prev->prev = *head;
    (*head)->prev->next = (*head)->next;
    if((*head)->next)
        (*head)->next->prev = (*head)->prev;
    (*head)->next = (*head)->prev;
    (*head)->NULL;
}
void sa(t_stack_node **a,bool print)
{
    swap(a);
    if(!print)
        ft_printf("sa\n");
}
void sb(t_stack_node **b,bool print)
{
    swap(b);
    if(!print)
        ft_printf("sb\n");
}
void ss(t_stack_node **a,t_stack_node **b, bool print)
{
    swap(a);
    swap(b);
    if(!print)
        ft_printf("ss\n");
}
