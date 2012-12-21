import java.io.BufferedReader;
import java.io.RandomAccessFile;

import java.nio.MappedByteBuffer;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

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

    public void openMap() {
        try {
            this.rFile = new RandomAccessFile(file, "r");
        } catch (FileNotFoundException f) {
            System.out.println("File not found for mapping: "+f);
        }


        this.fChannel = rFile.getChannel();
        try {
            this.fSize = fChannel.size();
            this.map = fChannel.map(FileChannel.MapMode.READ_ONLY, 0, fSize);
        } catch (IOException e) {
            System.out.println("size() error: "+e);
        }
    }

    public Relation setRelation() {
        Relation relation = new Relation();
        Path path = Paths.get(this.file);
        Charset charset = Charset.forName("US-ASCII");

        try (BufferedReader reader = Files.newBufferedReader(path, charset)) {
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
