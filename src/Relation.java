import java.util.Vector;

public class Relation {
    public static final Byte INT = 0x00;
    public static final Byte STRING = 0x01;
    public static final int NUM_RECS = 100;
    
    public Meta meta;
    public Vector<Record> records;

    public Relation() {
        this.meta = new Meta();
        this.records = new Vector<Record>(NUM_RECS);
    }

    public void print() {
        this.meta.print();

        for (int i=0; i<meta.numRows; i++) {
            records.get(i).print();
        }
    }
}
