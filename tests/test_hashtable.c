#include <string.h>
#include <assert.h>

#include "hashtable.h"

int main(void)
{
    Hashtable table;
    htable_init(&table);

    htable_set(&table, "key", "value");
    htable_set(&table, "key2", "value2");

    assert(strcmp(htable_get(&table, "key"), "value") == 0);
    assert(strcmp(htable_get(&table, "key2"), "value2") == 0);

    htable_set(&table, "key3", "value3");
    htable_set(&table, "key4", "value4");
    htable_set(&table, "key5", "value5");
    htable_set(&table, "key6", "value6");
    htable_set(&table, "key7", "value7");
    htable_set(&table, "key8", "value8");
    htable_set(&table, "key9", "value9");
    htable_set(&table, "key10", "value10");
    htable_set(&table, "key11", "value11");
    htable_set(&table, "key12", "value12");
    htable_set(&table, "key13", "value13");
    htable_set(&table, "key14", "value14");
    htable_set(&table, "key15", "value15");
    htable_set(&table, "key16", "value16");
    htable_set(&table, "key17", "value17");
    htable_set(&table, "key18", "value18");
    htable_set(&table, "key19", "value19");
    htable_set(&table, "key20", "value20");
    htable_set(&table, "key21", "value21");
    htable_set(&table, "key22", "value22");
    htable_set(&table, "key23", "value23");
    htable_set(&table, "key24", "value24");
    htable_set(&table, "key25", "value25");
    htable_set(&table, "key26", "value26");
    htable_set(&table, "key27", "value27");
    htable_set(&table, "key28", "value28");
    htable_set(&table, "key29", "value29");
    htable_set(&table, "key30", "value30");
    htable_set(&table, "key31", "value31");
    htable_set(&table, "key32", "value32");
    htable_set(&table, "key33", "value33");
    htable_set(&table, "key34", "value34");
    htable_set(&table, "key35", "value35");
    htable_set(&table, "key36", "value36");
    htable_set(&table, "key37", "value37");
    htable_set(&table, "key38", "value38");
    htable_set(&table, "key39", "value39");
    htable_set(&table, "key40", "value40");
    htable_set(&table, "key41", "value41");
    htable_set(&table, "key42", "value42");
    htable_set(&table, "key43", "value43");
    htable_set(&table, "key44", "value44");
    htable_set(&table, "key45", "value45");
    htable_set(&table, "key46", "value46");
    htable_set(&table, "key47", "value47");
    htable_set(&table, "key48", "value48");
    htable_set(&table, "key49", "value49");
    htable_set(&table, "key50", "value50");
    htable_set(&table, "key51", "value51");
    htable_set(&table, "key52", "value52");
    htable_set(&table, "key53", "value53");
    htable_set(&table, "key54", "value54");
    htable_set(&table, "key55", "value55");
    htable_set(&table, "key56", "value56");
    htable_set(&table, "key57", "value57");
    htable_set(&table, "key58", "value58");
    htable_set(&table, "key59", "value59");
    htable_set(&table, "key60", "value60");
    htable_set(&table, "key61", "value61");
    htable_set(&table, "key62", "value62");
    htable_set(&table, "key63", "value63");
    htable_set(&table, "key64", "value64");
    htable_set(&table, "key65", "value65");
    htable_set(&table, "key66", "value66");
    htable_set(&table, "key67", "value67");
    htable_set(&table, "key68", "value68");
    htable_set(&table, "key69", "value69");
    htable_set(&table, "key70", "value70");
    htable_set(&table, "key71", "value71");

    assert(strcmp(htable_get(&table, "key28"), "value28") == 0);
    assert(strcmp(htable_get(&table, "key44"), "value44") == 0);
    assert(strcmp(htable_get(&table, "key71"), "value71") == 0);
    assert(strcmp(htable_get(&table, "key"), "value") == 0);

    assert(htable_get(&table, "unknown_key") == NULL);

    htable_free(&table);
}
