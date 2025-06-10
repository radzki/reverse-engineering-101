#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TARGET_SUM 867
#define MAX_LENGTH 20

// Our valid ASCII values for a-z A-Z 0-9
int valid_ascii[62];
int valid_count = 62;

// Initialize valid ASCII values
void init_ascii_values() {
    int idx = 0;
    
    // 0-9: ASCII 48-57
    for (int i = 48; i <= 57; i++) {
        valid_ascii[idx++] = i;
    }
    
    // A-Z: ASCII 65-90
    for (int i = 65; i <= 90; i++) {
        valid_ascii[idx++] = i;
    }
    
    // a-z: ASCII 97-122
    for (int i = 97; i <= 122; i++) {
        valid_ascii[idx++] = i;
    }
}

// Calculate ASCII sum
int calculate_sum(char *str, int length) {
    int sum = 0;
    for (int i = 0; i < length; i++) {
        sum += str[i];
    }
    return sum;
}

// Smart random generation - much faster than exhaustive search
int generate_smart_random(char *password, int length) {
    int attempts = 0;
    const int max_attempts = 100000;
    
    while (attempts < max_attempts) {
        int remaining_sum = TARGET_SUM;
        int valid = 1;
        
        // Fill first length-1 characters smartly
        for (int i = 0; i < length - 1; i++) {
            int remaining_chars = length - i - 1;
            
            // Calculate bounds for this character
            int min_needed = remaining_sum - (remaining_chars * 122); // max remaining
            int max_allowed = remaining_sum - (remaining_chars * 48); // min remaining
            
            // Find valid characters in our set within bounds
            int valid_chars[62];
            int valid_char_count = 0;
            
            for (int j = 0; j < valid_count; j++) {
                int ascii_val = valid_ascii[j];
                if (ascii_val >= min_needed && ascii_val <= max_allowed) {
                    valid_chars[valid_char_count++] = ascii_val;
                }
            }
            
            if (valid_char_count == 0) {
                valid = 0;
                break;
            }
            
            // Pick random valid character
            int char_val = valid_chars[rand() % valid_char_count];
            password[i] = char_val;
            remaining_sum -= char_val;
        }
        
        if (!valid) {
            attempts++;
            continue;
        }
        
        // Check if remaining sum is a valid character
        int found_last = 0;
        for (int i = 0; i < valid_count; i++) {
            if (valid_ascii[i] == remaining_sum) {
                password[length - 1] = remaining_sum;
                password[length] = '\0';
                found_last = 1;
                break;
            }
        }
        
        if (found_last) {
            return 1; // Success!
        }
        
        attempts++;
    }
    
    return 0; // Failed
}

// Generate a diverse sample of passwords
void generate_sample_passwords(int length, int sample_size, FILE* file) {
    printf("Generating %d sample passwords of length %d...\n", sample_size, length);
    
    char password[MAX_LENGTH + 1];
    int generated = 0;
    int attempts = 0;
    
    fprintf(file, "# Length %d sample passwords (%d generated)\n", length, sample_size);
    
    while (generated < sample_size && attempts < sample_size * 10) {
        if (generate_smart_random(password, length)) {
            // Verify it's correct
            int sum = calculate_sum(password, length);
            if (sum == TARGET_SUM) {
                fprintf(file, "%s\n", password);
                
                // Show first few on console
                if (generated < 10) {
                    printf("  '%s' (sum: %d)\n", password, sum);
                }
                
                generated++;
            }
        }
        attempts++;
    }
    
    fprintf(file, "\n");
    printf("Generated %d valid passwords of length %d\n\n", generated, length);
}

// Exhaustive generation for very small feasible lengths
void generate_exhaustive_small(int length, FILE* file) {
    printf("Exhaustive generation for length %d...\n", length);
    
    char password[MAX_LENGTH + 1];
    password[length] = '\0';
    
    int found = 0;
    long long total_combinations = 1;
    
    // Calculate total combinations
    for (int i = 0; i < length; i++) {
        total_combinations *= valid_count;
    }
    
    if (total_combinations > 10000000) {  // 10 million limit
        printf("Too many combinations (%lld) - using sampling instead\n", total_combinations);
        generate_sample_passwords(length, 1000, file);
        return;
    }
    
    fprintf(file, "# Length %d exhaustive results\n", length);
    
    // Generate all combinations
    int indices[20] = {0};
    long long count = 0;
    
    while (count < total_combinations) {
        // Build current password from indices
        for (int i = 0; i < length; i++) {
            password[i] = valid_ascii[indices[i]];
        }
        
        // Check if it sums to target
        if (calculate_sum(password, length) == TARGET_SUM) {
            fprintf(file, "%s\n", password);
            
            if (found < 20) {  // Show first 20 on console
                printf("  '%s'\n", password);
            }
            found++;
        }
        
        // Increment indices
        int pos = length - 1;
        indices[pos]++;
        
        while (pos >= 0 && indices[pos] >= valid_count) {
            indices[pos] = 0;
            pos--;
            if (pos >= 0) {
                indices[pos]++;
            }
        }
        
        if (pos < 0) break;
        count++;
        
        // Progress indicator
        if (count % 1000000 == 0) {
            printf("Checked %lld combinations, found %d valid...\n", count, found);
        }
    }
    
    fprintf(file, "\n");
    printf("Found %d valid passwords of length %d\n\n", found, length);
}

int main() {
    srand(time(NULL));
    init_ascii_values();
    
    printf("Practical Password Generator for ASCII sum = %d\n\n", TARGET_SUM);
    
    // Open output file
    FILE* file = fopen("ascii_867_passwords.txt", "w");
    if (!file) {
        printf("Error: Could not create output file!\n");
        return 1;
    }
    
    // Write header
    fprintf(file, "# ASCII 867 Password Solutions\n");
    fprintf(file, "# Target sum: %d\n", TARGET_SUM);
    fprintf(file, "# Character set: 0-9 A-Z a-z\n");
    fprintf(file, "# Generated using smart sampling for large sets\n\n");
    
    // Analyze bounds first
    printf("=== Feasibility Analysis ===\n");
    for (int len = 1; len <= 15; len++) {
        int min_sum = len * 48;
        int max_sum = len * 122;
        
        if (TARGET_SUM >= min_sum && TARGET_SUM <= max_sum) {
            printf("Length %d: POSSIBLE (bounds: %d-%d)\n", len, min_sum, max_sum);
        } else {
            printf("Length %d: IMPOSSIBLE (bounds: %d-%d)\n", len, min_sum, max_sum);
        }
    }
    printf("\n");
    
    // Generate passwords for feasible lengths
    printf("=== Password Generation ===\n");
    
    for (int len = 8; len <= 12; len++) {
        int min_sum = len * 48;
        int max_sum = len * 122;
        
        if (TARGET_SUM >= min_sum && TARGET_SUM <= max_sum) {
            if (len <= 6) {
                generate_exhaustive_small(len, file);
            } else {
                // Use sampling for larger lengths
                int sample_size = (len <= 8) ? 10000 : 5000;
                generate_sample_passwords(len, sample_size, file);
            }
        }
    }
    
    fclose(file);
    
    printf("=== Complete ===\n");
    printf("Results saved to: ascii_867_passwords.txt\n");
    printf("This approach generates practical samples rather than\n");
    printf("attempting impossible exhaustive enumeration.\n");
    
    return 0;
}