#include "dbselector.h"
#include "dbmanager.h"
#include <QSqlQuery>
#include <QSqlRecord>

using namespace DBTypes;

DBSelector::DBSelector()
    : m_dbManager {DBManager::instance()}
{
}

DBResult DBSelector::selectAll(const std::string& tableName, std::vector<QVariantList>& returnData)
{
    const std::string query {generateQuery(tableName)};
    DBResult result;
    QSqlQuery resultQuery;
    std::tie(result, resultQuery) = m_dbManager.execute(query);

    if (result == DBResult::OK) {
        while (resultQuery.next()) {
            const QSqlRecord& resultRecord = resultQuery.record();
            QVariantList result;
            for (int i = 0; i < resultRecord.count(); ++i) {
                result.push_back(resultRecord.value(i));
            }
            returnData.push_back(std::move(result));
        }
    }

    return result;
}

std::string DBSelector::generateQuery(const std::string& tableName) const
{
    std::string query = "SELECT rowid, * FROM " + tableName;
    return query;
}
