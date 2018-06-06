# Lem_in

Parallel pathfinder to distribute multiple ants in the least amount of steps using Dijkstra's algorithm.

## Installation:

`git clone https://github.com/fpetras/lem_in.git && cd lem_in && make`

## Usage:

```
usage: lem-in [-v] < map
       lem-in [-v] -f map
```

The program will receive the data describing an ant farm in the following format:

```
number_of_ants
rooms
links
```

The rooms are defined by: **name coord_x coord_y**\
The links are defined by: **name1-name2**

Lines starting with **#** are comments\
Lines starting with **##** are commands that modify the property of the following line

**##start** and **##end** signal the ant farm's entrance and exit

Example:

```
42
##start
1 23 3
2 16 7
#comment
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end
0 9 5
0-4
0-6
1-3
4-3
5-2
3-5
#another comment
4-2
2-1
7-6
7-2
7-4
6-5
```

Which corresponds to the following representation:

```
            _______________
           /               \
  ______[5]----[3]----[1]   |
 /              |    /      |
[6]-----[0]----[4]  /       |
\    _________/ |  /        |
 \ /           [2]/________/
  [7]_________/
```

### In action:

![GIF](http://g.recordit.co/suXfwLMWeZ.gif)

## Code snippets:

Pathfinder:

```C
int    pathfinder(int ***routetab, int size, t_array *sol, int end)
{
    int node;

    node = get_min_path(*routetab, size, ARRAY_DATA(sol, sol->size - 1), end);
    if (node == end)
    {
        if (sol->size == 1)
            (*routetab)[ARRAY_DATA(sol, sol->size - 1)][end] = size + 1;
        fta_append(sol, &node, 1);
        return (1);
    }
    while (node < size && (*routetab)[end][node] < size + 1 &&
        !in_solutions(sol, node))
    {
        (*routetab)[ARRAY_DATA(sol, sol->size - 1)][end] = size + 1;
        fta_append(sol, &node, 1);
        (*routetab)[end][node] = size + 1;
        if (pathfinder(routetab, size, sol, end))
            return (1);
        fta_popback(sol, 1);
        node = get_min_path(*routetab, size,
            ARRAY_DATA(sol, sol->size - 1), end);
    }
    return (0);
}

int    run_pathfinder(int **route, t_array ***sols,
                t_node *r, t_lem_in *l)
{
    t_array     sol;
    int         nb_sols;
    int         turns;
    int         start;

    sol = NEW_ARRAY(int);
    nb_sols = 0;
    turns = 0;
    start = get_nodes_index(r, l, l->start);
    fta_append(&sol, &start, 1);
    while (pathfinder(&route, l->nb_rooms, &sol, get_nodes_index(r, l, l->end)))
    {
        *sols = append_solutions((*sols), nb_sols++, sol);
        if (turns_counter((*sols), l->nb_ants, nb_sols) > turns && turns != 0)
        {
            fta_clear((*sols)[--nb_sols]);
            free((*sols)[nb_sols]);
        }
        turns = turns_counter((*sols), l->nb_ants, nb_sols);
        fta_clear(&sol);
        sol = NEW_ARRAY(int);
        fta_append(&sol, &start, 1);
    }
    fta_clear(&sol);
    return (nb_sols);
}
```

## Credits

Collaboration between

|<img src="https://avatars0.githubusercontent.com/u/34797639" width="75px;"/>|<img src="https://avatars0.githubusercontent.com/u/6814254" width="75px;"/>|
| --------- | --------- |
| [Fabian Petras](https://github.com/fpetras) | [Rizky Ario](https://github.com/rizkyario) |

## [Subject](https://github.com/fpetras/42-subjects/blob/master/lem-in.en.pdf "lem-in.en.pdf")
