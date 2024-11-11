#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "hashtable.h"
#include "log.h"

int main(void)
{
    log_init();

    struct Hashtable table;
    htable_init(&table);

    htable_insert(&table, "key", "value");
    htable_insert(&table, "key2", "value2");

    assert(strcmp(htable_get(&table, "key"), "value") == 0);
    assert(strcmp(htable_get(&table, "key2"), "value2") == 0);

    htable_insert(&table, "key3", "value3");
    htable_insert(&table, "key4", "value4");
    htable_insert(&table, "key5", "value5");
    htable_insert(&table, "key6", "value6");
    htable_insert(&table, "key7", "value7");
    htable_insert(&table, "key8", "value8");
    htable_insert(&table, "key9", "value9");
    htable_insert(&table, "key10", "value10");
    htable_insert(&table, "key11", "value11");
    htable_insert(&table, "key12", "value12");
    htable_insert(&table, "key13", "value13");
    htable_insert(&table, "key14", "value14");
    htable_insert(&table, "key15", "value15");
    htable_insert(&table, "key16", "value16");
    htable_insert(&table, "key17", "value17");
    htable_insert(&table, "key18", "value18");
    htable_insert(&table, "key19", "value19");
    htable_insert(&table, "key20", "value20");
    htable_insert(&table, "key21", "value21");
    htable_insert(&table, "key22", "value22");
    htable_insert(&table, "key23", "value23");
    htable_insert(&table, "key24", "value24");
    htable_insert(&table, "key25", "value25");
    htable_insert(&table, "key26", "value26");
    htable_insert(&table, "key27", "value27");
    htable_insert(&table, "key28", "value28");
    htable_insert(&table, "key29", "value29");
    htable_insert(&table, "key30", "value30");
    htable_insert(&table, "key31", "value31");
    htable_insert(&table, "key32", "value32");
    htable_insert(&table, "key33", "value33");
    htable_insert(&table, "key34", "value34");
    htable_insert(&table, "key35", "value35");
    htable_insert(&table, "key36", "value36");
    htable_insert(&table, "key37", "value37");
    htable_insert(&table, "key38", "value38");
    htable_insert(&table, "key39", "value39");
    htable_insert(&table, "key40", "value40");
    htable_insert(&table, "key41", "value41");
    htable_insert(&table, "key42", "value42");
    htable_insert(&table, "key43", "value43");
    htable_insert(&table, "key44", "value44");
    htable_insert(&table, "key45", "value45");
    htable_insert(&table, "key46", "value46");
    htable_insert(&table, "key47", "value47");
    htable_insert(&table, "key48", "value48");
    htable_insert(&table, "key49", "value49");
    htable_insert(&table, "key50", "value50");
    htable_insert(&table, "key51", "value51");
    htable_insert(&table, "key52", "value52");
    htable_insert(&table, "key53", "value53");
    htable_insert(&table, "key54", "value54");
    htable_insert(&table, "key55", "value55");
    htable_insert(&table, "key56", "value56");
    htable_insert(&table, "key57", "value57");
    htable_insert(&table, "key58", "value58");
    htable_insert(&table, "key59", "value59");
    htable_insert(&table, "key60", "value60");
    htable_insert(&table, "key61", "value61");
    htable_insert(&table, "key62", "value62");
    htable_insert(&table, "key63", "value63");
    htable_insert(&table, "key64", "value64");
    htable_insert(&table, "key65", "value65");
    htable_insert(&table, "key66", "value66");
    htable_insert(&table, "key67", "value67");
    htable_insert(&table, "key68", "value68");
    htable_insert(&table, "key69", "value69");
    htable_insert(&table, "key70", "value70");
    htable_insert(&table, "key71", "value71");

    assert(strcmp(htable_get(&table, "key28"), "value28") == 0);
    assert(strcmp(htable_get(&table, "key44"), "value44") == 0);
    assert(strcmp(htable_get(&table, "key71"), "value71") == 0);
    assert(strcmp(htable_get(&table, "key"), "value") == 0);

    assert(htable_get(&table, "unknown_key") == NULL);

    htable_free(&table);

    htable_init(&table);

    htable_insert(&table, "id", "value");
    htable_insert(&table, "class", "value_");

    htable_print(&table);
    printf("\n");

    htable_free(&table);
}
