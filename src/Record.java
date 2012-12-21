import java.util.Vector;

public class Record {
    public Vector<String> data;

    public Record(int size) {
        this.data = new Vector<String>(size);
    }

    public void print() {
        for (int i=0; i<data.size(); i++)
            System.out.print(data.get(i)+" ");
        System.out.println();
    }
}
