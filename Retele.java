import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

class Retele extends Task {
    Integer numberOfFamilies;

    Integer numberOfRelations;

    Integer numberOfSpies;

    Integer[][] relations;

    boolean oracleAnswer;

    Integer variablesNumber;

    List<Integer> variables;

    List<Integer> decodifiedVariables;

    @Override
    public void solve() throws IOException, InterruptedException {
        readProblemData();
        formulateOracleQuestion();
        askOracle();
        decipherOracleAnswer();
        writeAnswer();
    }

    @Override
    public void readProblemData() throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(inFilename));

        // split the first line to take each input
        String[] firstLine = reader.readLine().split("\\s");

        numberOfFamilies = Integer.parseInt(firstLine[0]);
        numberOfRelations = Integer.parseInt(firstLine[1]);
        numberOfSpies = Integer.parseInt(firstLine[2]);

        relations = new Integer[numberOfRelations][2];

        for (int i = 0; i < numberOfRelations; i++) {
            // split the current line to get each family
            String[] currentLine = reader.readLine().split("\\s");

            relations[i][0] = Integer.parseInt(currentLine[0]);
            relations[i][1] = Integer.parseInt(currentLine[1]);
        }
    }

    @Override
    public void formulateOracleQuestion() throws IOException {
        FileWriter writer = new FileWriter(oracleInFilename);

        int numberOfVariables = numberOfFamilies * numberOfSpies;

        int numberOfClauses = numberOfFamilies
                + ((numberOfSpies - 1) * numberOfSpies / 2 * numberOfFamilies)
                + relations.length * numberOfSpies;

        writer.write("p cnf " + numberOfVariables + " " + numberOfClauses + "\n");

        // we take each family and write it's clause
        for (int i = 1; i < numberOfFamilies * numberOfSpies; i += numberOfSpies) {
            // first, each family can take any of the spies available
            for (int j = 0; j < numberOfSpies; j++) {
                int familyTaken = i + j;

                writer.write(familyTaken + " ");
            }

            writer.write("0\n");

            // then the clause that makes sure that Registre family has taken only Registre spy
            for (int j = 0; j < numberOfSpies - 1; j++) {
                int firstSpy = -(i + j);

                for (int k = j + 1; k < numberOfSpies; k++) {
                    int secondSpy = -(i + k);

                    writer.write(firstSpy + " " + secondSpy + " 0\n");
                }
            }
        }

        // we take each family relation now
        for (int i = 1; i <= relations.length; i++) {
            int firstFamily = relations[i - 1][0];
            int secondFamily = relations[i - 1][1];

            // codify them
            int firstFamilyTaken = 1 + (firstFamily - 1) * numberOfSpies;
            int secondFamilyTaken = 1 + (secondFamily - 1) * numberOfSpies;

            // write the clause that makes sure that 2 families that are in relation don't take
            // the same spy
            for (int j = 0; j < numberOfSpies; j++) {
                int firstSpy = -(firstFamilyTaken + j);
                int secondSpy = -(secondFamilyTaken + j);

                writer.write(firstSpy + " " + secondSpy + " 0\n");
            }
        }

        writer.flush();
        writer.close();
    }

    @Override
    public void decipherOracleAnswer() throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader(oracleOutFilename));

        oracleAnswer = Boolean.parseBoolean(reader.readLine().split("\\s")[0]);

        if (oracleAnswer) {
            variablesNumber = Integer.parseInt(reader.readLine().split("\\s")[0]);

            // the initial answer which contains each literal value
            variables = new ArrayList<Integer>();

            String[] variableLine = reader.readLine().split("\\s");

            for (int i = 0; i < variablesNumber; i++) {
                variables.add(i, Integer.parseInt(variableLine[i]));
            }

            // decoding the oracleAnswer
            decodifiedVariables = new ArrayList<Integer>();

            for (int i = 0; i < variablesNumber; i += numberOfSpies) {
                for (int  j = 0; j < numberOfSpies; j++) {
                    if (variables.get(i+ j) > 0) {
                        decodifiedVariables.add(j + 1);

                        break;
                    }
                }
            }
        }
    }

    @Override
    public void writeAnswer() throws IOException {
        FileWriter out = new FileWriter(outFilename);

        if (oracleAnswer) {
            out.write("True \n");

            // write each spy assigned for each family
            for (int i = 0; i < decodifiedVariables.size(); i++) {
                out.write(decodifiedVariables.get(i) + " ");
            }

            out.close();
        } else {
            out.write("False \n");
            out.close();
        }
    }
}