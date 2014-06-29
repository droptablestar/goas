public class Operator {
    public Relation Scan(String filename, Relation relation) {
        MMap mmap = new MMap(filename);

        relation = mmap.openMap();
        // relation = mmap.setRelation();

        // relation.meta.print();
        return relation;
    }
}
