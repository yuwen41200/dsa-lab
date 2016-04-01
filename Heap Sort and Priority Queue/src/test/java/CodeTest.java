/**
 * Homework #2 Sort (Binary Input)
 * Unit Test
 */

import org.junit.Test;
import static org.junit.Assert.assertEquals;
import org.msgpack.core.MessagePack;
import org.msgpack.core.MessagePacker;
import org.msgpack.core.MessageUnpacker;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Arrays;
import java.util.concurrent.ThreadLocalRandom;

public class CodeTest {

@Test
public void test() throws Exception {

	final int dataSize1 = 1;
	final int dataSize2 = 2;
	final int dataSize3 = 4;
	final int dataSize4 = 8;
	final int dataSize5 = 16;

	int[] dataSet1 = new int[dataSize1];
	int[] dataSet2 = new int[dataSize2];
	int[] dataSet3 = new int[dataSize3];
	int[] dataSet4 = new int[dataSize4];
	int[] dataSet5 = new int[dataSize5];

	for (int i = 0; i < dataSize1; i++)
		dataSet1[i] = ThreadLocalRandom.current().nextInt();
	for (int i = 0; i < dataSize2; i++)
		dataSet2[i] = ThreadLocalRandom.current().nextInt();
	for (int i = 0; i < dataSize3; i++)
		dataSet3[i] = ThreadLocalRandom.current().nextInt();
	for (int i = 0; i < dataSize4; i++)
		dataSet4[i] = ThreadLocalRandom.current().nextInt();
	for (int i = 0; i < dataSize5; i++)
		dataSet5[i] = ThreadLocalRandom.current().nextInt();
	MessagePacker packer = MessagePack.newDefaultPacker(new FileOutputStream("input.txt"));
	packer.packInt(5);
	packer.packArrayHeader(dataSize1);
	for (int i = 0; i < dataSize1; i++)
		packer.packInt(dataSet1[i]);
	packer.packArrayHeader(dataSize2);
	for (int i = 0; i < dataSize2; i++)
		packer.packInt(dataSet2[i]);
	packer.packArrayHeader(dataSize3);
	for (int i = 0; i < dataSize3; i++)
		packer.packInt(dataSet3[i]);
	packer.packArrayHeader(dataSize4);
	for (int i = 0; i < dataSize4; i++)
		packer.packInt(dataSet4[i]);
	packer.packArrayHeader(dataSize5);
	for (int i = 0; i < dataSize5; i++)
		packer.packInt(dataSet5[i]);
	packer.close();

	Code.main(null);
	Arrays.sort(dataSet1);
	Arrays.sort(dataSet2);
	Arrays.sort(dataSet3);
	Arrays.sort(dataSet4);
	Arrays.sort(dataSet5);

	MessageUnpacker unpacker = MessagePack.newDefaultUnpacker(new FileInputStream("output.txt"));
	assertEquals(dataSize1, unpacker.unpackArrayHeader());
	for (int i = 0; i < dataSize1; i++)
		assertEquals(dataSet1[i], unpacker.unpackInt());
	assertEquals(dataSize2, unpacker.unpackArrayHeader());
	for (int i = 0; i < dataSize2; i++)
		assertEquals(dataSet2[i], unpacker.unpackInt());
	assertEquals(dataSize3, unpacker.unpackArrayHeader());
	for (int i = 0; i < dataSize3; i++)
		assertEquals(dataSet3[i], unpacker.unpackInt());
	assertEquals(dataSize4, unpacker.unpackArrayHeader());
	for (int i = 0; i < dataSize4; i++)
		assertEquals(dataSet4[i], unpacker.unpackInt());
	assertEquals(dataSize5, unpacker.unpackArrayHeader());
	for (int i = 0; i < dataSize5; i++)
		assertEquals(dataSet5[i], unpacker.unpackInt());
	unpacker.close();

}

}
