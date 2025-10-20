import os.path

import pymupdf4llm
import pathlib


INPUT_PDF = "Historia_splaty.pdf"
OUTPUT_MARKDOWN = "Historia_splaty.md"


def pdf2markdown(input_pdf, output_markdown):
    if os.path.exists(output_markdown):
        print(f'{output_markdown} already exists, using it to save time')
        return

    md_text = pymupdf4llm.to_markdown(input_pdf)
    pathlib.Path(output_markdown).write_bytes(md_text.encode())


def process_mortgage(markdown_file):
    total_interests = 0

    with open(markdown_file, encoding='utf-8') as f:
        for line in f.readlines():
            if 'pozaplanowej' in line:
                continue

            if line.startswith('Spłata raty '):
                line = line.replace('Spłata raty ', '')
                money = line.split('**')
                total_interests += float(money[9].replace(' ', '').replace(',', '.'))

    return total_interests


if __name__ == '__main__':
    pdf2markdown(INPUT_PDF, OUTPUT_MARKDOWN)
    interests_paid = process_mortgage(OUTPUT_MARKDOWN)
    print(f'In total paid {interests_paid} PLN interests')
