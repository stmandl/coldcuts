facts = [('m',3.28,'ft'),
         ('ft',12,'in'),
         ('hr',60,'min'),
         ('min',60,'sec')]

queries = [(2,'m','in'),
           (13,'in','m'),
           (13,'in','hr')]

from collections import defaultdict

def compile_facts(facts):
    G = defaultdict(list)
    for from_unit, factor, to_unit in facts:
        G[from_unit].append((to_unit,factor))
        G[to_unit].append((from_unit,1/factor))
    return G

FactGraph = compile_facts(facts)
print(FactGraph)

def query_(q, G,History):    
    amount, from_unit, to_unit = q
    if from_unit == to_unit:
        return amount
    successors = G[from_unit]
    for unit, factor in successors:
        if unit not in History:
            History.add(unit)
            res = query_((amount*factor, unit, to_unit),G,History)
            if res is not None:
                return res
    return None

def query(q, G):
    res = query_(q,G,set([]))
    if res is not None:
        return res
    else:
        return "not supported"

for q in queries:
    print(q,query(q,FactGraph))