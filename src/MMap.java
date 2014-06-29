import java.io.BufferedReader;
import java.io.FileReader;
import java.io.RandomAccessFile;

import java.nio.MappedByteBuffer;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.ByteOrder;

import java.util.Vector;

import java.io.FileNotFoundException;
import java.io.IOException;

public class MMap {
    private String file;
    private FileChannel fChannel;
    private RandomAccessFile rFile;
    private MappedByteBuffer map;
    private long fSize;
    
    public MMap(String file) {
        this.file = file;

        // TODO: might be interesting to try map.load() and look at the effects
    }

    public Relation openMap() {
        try {
            this.rFile = new RandomAccessFile(file, "r");
        } catch (FileNotFoundException f) {
            System.out.println("File not found for mapping: "+f);
        }

        this.fChannel = rFile.getChannel();
        try {
            this.fSize = fChannel.size();
            this.map = fChannel.map(FileChannel.MapMode.READ_ONLY, 0, fSize);
            this.map.order(ByteOrder.LITTLE_ENDIAN);
        } catch (IOException e) {
            System.out.println("size() error: "+e);
        }

        Relation relation = new Relation();
        short numCols = this.map.getShort();
        int numRows = this.map.getInt();
        relation.meta.numCols = numCols;
        relation.meta.numRows = numRows;
        relation.meta.columnTypes = new Vector<Byte>(numCols);
        relation.meta.columnNames = new Vector<String>(numCols);

        int index = 6;
        for (int i=0; i<numCols; i++) {
            relation.meta.columnTypes.add(this.map.get(index++));
            
            char in = '\0';
            String name = "";
            do {
                in = (char)this.map.get(index++);
                name += in;
            } while (in != '\0');
            relation.meta.columnNames.add(name);
            // System.out.println("i: "+i+" ["+name+"]");
        }
        for (int i=0; i<numRows; i++) {
            for (int j=0; j<numCols; j++) {
                if (relation.meta.columnTypes.get(j) == Relation.INT) {
                    
                }
            }
        }
            
        return relation;
    }

    public Relation setRelation() {
        Relation relation = new Relation();

        try {
            BufferedReader reader = new BufferedReader(
                new FileReader(this.file));
            String line = null;
            if ((line = reader.readLine()) == null) {
                System.out.println("File is empty.");
                throw new IOException();
            }
            /* this will set up the meta data for the relation */
            String data[] = line.split("\t");
            int numCols = data.length;
            relation.meta.numCols = numCols;
            relation.meta.columnNames = new Vector<String>(numCols);
            for (int i=0; i<numCols; i++)
                relation.meta.columnNames.add(data[i]);

            int rows = 0;
            while ((line = reader.readLine()) != null) {
                Record rec = new Record(numCols);
                data = line.split("\t");
                for (int i=0; i<numCols; i++) {
                    rec.data.add(data[i]);
                }
                relation.records.add(rec);
                rows++;
            }

            relation.meta.numRows = rows;
        } catch(IOException e) {
            System.err.format("IOException: %s%n", e);
        }
                    
        return relation;
    }
}
