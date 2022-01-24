import java.io.*;
import java.util.*;
import java.util.stream.*;

public class Registre extends Task {
    private final List<List<Integer>> relationships = new ArrayList<>();
    private final List<List<Integer>> noRelationships = new ArrayList<>();
    String task2InFilename;
    String task2OutFilename;
    private int families;
    private int totalNoRelationships;
    private int dimension;
    private String result;
    private List<Integer> solutions;

    @Override
    public void solve() throws IOException, InterruptedException {
        task2InFilename = inFilename + "_t2";
        task2OutFilename = outFilename + "_t2";
        Registre task2Solver = new Registre();
        task2Solver.addFiles(task2InFilename, oracleInFilename, oracleOutFilename, task2OutFilename);
        readProblemData();

        // Do Task 2 until the result is "True"
        for (; dimension > 0; --dimension) {
            reduceToRegistre();
            task2Solver.solve();
            extractAnswerFromRegistre();
            if (result.equals("True")) {
                break;
            }
        }

        writeAnswer();
    }

    @Override
    public void readProblemData() {
        try {
            File file = new File(inFilename);
            Scanner scanner = new Scanner(file);

            families = scanner.nextInt();
            int totalRelationships = scanner.nextInt();

            // Calculate total number of no-edge relationships using the total number of
            // vertices in a complete graph and the total number of relationships from the input
            totalNoRelationships = families * (families - 1) / 2 - totalRelationships;
            // First Method for Clique Size: used the total number of vertices in a complete graph
            dimension = (int) Math.floor((1 + Math.sqrt(1 + 8 * totalNoRelationships)) / 2);

            for (int i = 0; i < families; ++i) {
                // Initialize the relationship list
                relationships.add(new ArrayList<>());
                // Create the lists for the list of no-edge relationships and add it
                List<Integer> numbers = Stream.iterate(0, n -> n + 1)
                        .limit(families)
                        .collect(Collectors.toList());
                numbers.remove(Integer.valueOf(i));
                noRelationships.add(numbers);
            }

            // Generate list of family indexes
            solutions = Stream.iterate(1, n -> n + 1)
                    .limit(families)
                    .collect(Collectors.toList());

            while (scanner.hasNext()) {
                int firstNode = scanner.nextInt();
                int secondNode = scanner.nextInt();
                // Add the relationship to the edge list
                relationships.get(firstNode - 1).add(secondNode - 1);
                // Remove the relationship from the non-edge list
                noRelationships.get(firstNode - 1).remove(Integer.valueOf(secondNode - 1));
                noRelationships.get(secondNode - 1).remove(Integer.valueOf(firstNode - 1));
            }

            // Second Method for Clique Size: used the internal degree of a node
            int max = 0;
            for (List<Integer> noRelationship : noRelationships) {
                if (max < noRelationship.size()) {
                    int size = noRelationship.size();
                    boolean found = noRelationship.stream()
                            .mapToInt(integer -> noRelationships.get(integer).size())
                            .noneMatch(curr -> curr < size);
                    if (found) {
                        max = noRelationship.size();
                    }
                }
            }

            // Use the best method for finding clique size
            if (max != 0 && dimension > max + 1) {
                dimension = max + 1;
            }
        } catch (FileNotFoundException e) {
            System.out.println("Input file not found.");
            e.printStackTrace();
        }
    }

    public void reduceToRegistre() throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(task2InFilename));
        writer.write(families + " " + totalNoRelationships + " " + dimension + "\n");

        // Write all non-edges
        for (int i = 0; i < noRelationships.size(); ++i) {
            for (int j = 0; j < noRelationships.get(i).size(); ++j) {
                if (noRelationships.get(i).get(j) + 1 > i + 1) {
                    writer.write((i + 1) + " " + (noRelationships.get(i).get(j) + 1) + "\n");
                }
            }
        }

        writer.flush();
        writer.close();
    }

    public void extractAnswerFromRegistre() {
        try {
            File file = new File(task2OutFilename);
            Scanner scanner = new Scanner(file);

            result = scanner.next();

            if (result.equals("True")) {
                while (scanner.hasNext()) {
                    int solution = scanner.nextInt();
                    // Remove from the list of family indexes the family given as solution
                    if (solution >= 0) {
                        solutions.remove(Integer.valueOf(solution));
                    }
                }
            }
        } catch (FileNotFoundException e) {
            System.out.println("Oracle output file not found.");
            e.printStackTrace();
        }
    }

    @Override
    public void writeAnswer() throws IOException {
        BufferedWriter writer = new BufferedWriter(new FileWriter(outFilename));

        // Write all remaining family indexes to output
        for (Integer solution : solutions) {
            writer.write(solution + " ");
        }

        writer.flush();
        writer.close();
    }
}