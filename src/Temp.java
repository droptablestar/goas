public class Temp {
    public static void main(String[] args) {
        Relation relation = new Relation();
        Operator operator = new Operator();

        relation = operator.Scan("../tst/oas_tables_text/100", relation);
        relation.print();
        // relation.meta.print();
    }
}
