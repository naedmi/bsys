#include <stdio.h>
#include <stdlib.h>

struct vector
{
    int *data;
    int size;
};

void v_free(struct vector *v);
void v_del(struct vector *v);
void v_ins(struct vector *v, int value);

int main()
{
    struct vector v = {(int *) malloc(sizeof(int)), 1};
    if (v.data == NULL)
    {
        fprintf(stderr, "memory allocation failed.\n");
        exit(1);
    }
    v.data[0] = 111;
    struct vector *vp = &v;
    v_ins(vp, 2);
    v_ins(vp, 3);
    v_ins(vp, 4);
    v_del(vp);

    printf("v.data[0]: %d\n", v.data[0]);
    printf("v.data[1]: %d\n", v.data[1]);
    printf("v.data[2]: %d\n", v.data[2]);
    printf("size: %d\n", v.size);

    v_free(vp);

    return 0;
}

/* inserts value in vector v. reallocs  */
void v_ins(struct vector *v, int value)
{
    v->data = (int *) realloc(v->data, v->size * sizeof(int));
    if (v->data == NULL)
    {
        fprintf(stderr, "memory allocation failed.\n");
        exit(1);
    }

    v->data[v->size++] = value;
}

void v_del(struct vector *v)
{
    v->size--;
    v->data = (int *) realloc(v->data, (v->size--) * sizeof(int));
    if (v->data == NULL)
    {
        fprintf(stderr, "memory allocation failed.\n");
        exit(1);
    }
}

void v_free(struct vector *v)
{
    free(v->data);
    v->size = 0;
}