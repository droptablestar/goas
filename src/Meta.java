import java.util.Vector;

public class Meta {
    public int numCols;
    public int numRows;
    public Vector<Byte> columnTypes;
    public Vector<String> columnNames;

    public void print() {
        System.out.println("Num rows: "+numRows+" Num cols: "+numCols);
        for (int i=0; i<numCols; i++)
            System.out.print(columnNames.get(i)+" ");
        System.out.println();
    }
}
