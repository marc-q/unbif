#ifndef __LLIST_H__
#define __LLIST_H__

typedef struct LList
{
	void         *data;
	struct LList *next;
} LList;

#define LLIST_FOR_EACH(pos, head) \
	for ((pos) = (head); (pos) != NULL; (pos) = (pos)->next)

LList * llist_last             (LList       *list);

LList * llist_append           (LList       *list,
                                void        *data);

LList * llist_prepend          (LList       *list,
                                void        *data);

void    llist_free             (LList       *list);
void    llist_free_full        (LList       *list,
                                void         free_func (void *data));

void *  llist_find_custom      (LList       *list,
                                int          func (const void *data,
                                                   const void *udata),
                                const void  *udata);

size_t  llist_length           (LList       *list);

#endif /* __LLIST_H__ */
