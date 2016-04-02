/**
 * Introduction to Algorithms 2016 Spring
 * Homework #1 Sort
 * by Yu-wen Pwu (rev1)
 */

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.lang.management.ManagementFactory;
import java.lang.management.MemoryPoolMXBean;
import java.lang.management.MemoryUsage;
import java.nio.charset.StandardCharsets;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Sort {
	public static void main(String[] args) {
		try {
			// Prepare the files
			Path input = FileSystems.getDefault().getPath("input.txt");
			Path output = FileSystems.getDefault().getPath("output.txt");
			BufferedReader bufferedReader = Files.newBufferedReader(input, StandardCharsets.US_ASCII);
			BufferedWriter bufferedWriter = Files.newBufferedWriter(output, StandardCharsets.US_ASCII,
					StandardOpenOption.WRITE, StandardOpenOption.CREATE, StandardOpenOption.TRUNCATE_EXISTING);
			// Actual sorting
			ArrayList<Integer> sequence = new ArrayList<>();
			int count = Integer.parseInt(bufferedReader.readLine());
			for (int i = 0; i < count; i++) {
				Scanner scanner = new Scanner(bufferedReader.readLine());
				while (scanner.hasNextInt())
					sequence.add(scanner.nextInt());
				sequence.sort(null);
				for (Integer j: sequence)
					bufferedWriter.write(j + " ");
				bufferedWriter.newLine();
				sequence.clear();
			}
			// Close the files
			bufferedReader.close();
			bufferedWriter.close();
		}
		catch (IOException e) {
			e.printStackTrace();
		}
		// Print peak memory usage
		try {
			String memoryUsage = "";
			List<MemoryPoolMXBean> pools = ManagementFactory.getMemoryPoolMXBeans();
			for (MemoryPoolMXBean pool : pools) {
				MemoryUsage peak = pool.getPeakUsage();
				memoryUsage += String.format("Peak %s memory used: %,d%n", pool.getName(), peak.getUsed());
				memoryUsage += String.format("Peak %s memory reserved: %,d%n", pool.getName(), peak.getCommitted());
			}
			System.out.println(memoryUsage);
		}
		catch (Throwable e) {
			e.printStackTrace();
		}
		System.exit(0);
	}
}
