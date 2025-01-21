void rotate_both(t_stack_node **a, t_stack_node **b, t_stack_node *cheapest_node)
{
    while(*b != cheapest_node->target_node && *a != cheapest_node)
    {
        rr(a,b,false);
        current_index(*a);
        current_index(*b);
    }
}
static void min_on_top(t_stack_node **a)
{
    while((*a)->nbr != find_min(*a)->nbr)
    {
        if(find_min(*a)->above_median)
            ra(a, false);
        else
            rra(a, false);
    }
}
static void set_target_b(t_stack_node *a, t_stack_node *b)
{
    t_stack_node *current_a;
    t_stack_node *target_node;
    long best_match_index;
    while(b)
    {
        best_match_index = LONG_MAX;
        current_a = a;
        while(current_a)
        {
            if(current_a->nbr > b->nbr && current_a->nbr < best_match_index)
            {
                best_match_index = current_a->nbr;
                target_node = current_a;
            }
            current_a = current_na->next;
        }
        if(best_match_index == LONG_MAX)
            b->target_node = find_min(a);
        else
            b->target_node = target_node;
        b = b->next;
    }
}
void init_nodes_b(t_stack_node *a, t_stack_node *b)
{
    current_index(a);
    current_index(b);
    set_target_b(a,b);
}